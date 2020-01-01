from flask import Flask, render_template, request
import json
import time
import datetime
import array

import socket

from random import randint

# Parse data to json struct for easy printing
def makeJSONreply(data, statusquery=False):
	timestamp = data['time']
	status = data['status']
	SNR = data['SNR']
	RSSI = data['RSSI']
	relays = data['relays']
	temperature = data['temperature']

	# Temperature is signed 8 bits
	if temperature & 0x80:
		temperature -= 256
	data['temperature'] = temperature

	# Relay status, 0=off, 1=on, 2=pending on
	relay1 = 0
	if relays & 0x01:
		relay1 = 1
	elif relays & 0x10:
		relay1 = 2

	relay2 = 0
	if relays & 0x02:
		relay2 = 1
	elif relays & 0x20:
		relay2 = 2

	# Comment: command failed or succesfull
	comment = "Epaonnistui"
	if status <> 0:
		comment = "Onnistui"

	timestring = datetime.datetime.fromtimestamp(timestamp).strftime('%d.%m.%Y %H:%M:%S')

	data_out = data
	data_out['timestring'] = timestring
	data_out['status'] = status,
	data_out['relay1'] = relay1
	data_out['relay2'] = relay2
	data_out['comment'] = comment

	# If command was status query, parse additional return data
	if statusquery:
		data_out['vsupply'] = ((data['user_data'] >> 8)& 0xFF) * 0.02	# Scaled such that 255 = 5.1 V => 0.02

		rf_temp = data['user_data'] & 0xFF	# Cast to signed
		if rf_temp & 0x80:
			rf_temp -= 256
		data_out['rf_temp'] = rf_temp

	return json.dumps(data_out)


# Error: fill the struct with zeros
def makeJSONerror():
	data = {'time': 0,
		'status': 0,
		'SNR': 0,
		'RSSI': 0,
		'channel': 0,
		'power': 0,
		'relays': 0,
		'temperature': 0,
		'pkg': 0,
		'user_data' : 0
		}

	return makeJSONreply(data)


# This function sends command to the server to be passed over air
def do_command(command, time1=0, time2=0):
	if command == 0:	# This would quit the server, not wanted here (yet)
		return

	now = int(time.time())
	if time1 == 0:
		time1 = now

	# Make command struct
	txCmd = array.array('B', [0 for _ in xrange(16)])	# 16 bytes, initialize to zero
	txCmd[0] = command & 0xFF	# Command byte
	txCmd[1] = 0x00			# Flags
	txCmd[2] = 0x00
	txCmd[3] = 0x00
	txCmd[4] = (time1 >> 24) & 0xFF	# Current time (or other time)
	txCmd[5] = (time1 >> 16) & 0xFF
	txCmd[6] = (time1 >> 8) & 0xFF
	txCmd[7] = time1 & 0xFF
	txCmd[8] = (time2 >> 24) & 0xFF			# Time 2
	txCmd[9] = (time2 >> 16) & 0xFF
	txCmd[10] = (time2 >> 8) & 0xFF
	txCmd[11] = time2 & 0xFF
	txCmd[12] = 0x00
	txCmd[13] = 0x00
	txCmd[14] = 0x00
	txCmd[15] = 0x00	# Package num & retransmits, handled by server

	# Open socket
	#sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	#sock.connect('pistoke')
	sock.connect(('127.0.0.1', 2222))

	# Send the command
	sock.send(txCmd)

	# Read data back
	rx_data = sock.recv(16)
	rxData = array.array('B', rx_data);

	rxTime = (rxData[0] << 24) + (rxData[1] << 16)+ (rxData[2] << 8) + rxData[3]
        user_data = (rxData[11] << 24) + (rxData[12] << 16)+ (rxData[13] << 8) + rxData[14]
	data = {'time': rxTime,
		'status': rxData[4],
		'SNR': rxData[5] * 0.25,
		'RSSI': rxData[6] - 164.0,
		'channel': rxData[7],
		'power': rxData[8],
		'relays': rxData[9],
		'temperature': rxData[10],
		'pkg': rxData[15],
		'user_data' : user_data
		}


	if rxData[4] == 250 and user_data != 0:
		# Requested info about the events

		# Read events from socket, this may take time...
		n_events = user_data
		print n_events, user_data
		raw_data = sock.recv(5*n_events)	# Every event is 5 bytes(mode + 4 x bytes of time)
		eventData = array.array('B', raw_data)

		data['events'] = []

		offset = 0
		while offset < n_events * 5:
			event_mode = eventData[offset]
			offset += 1
			event_time = eventData[offset] << 24
			offset += 1
			event_time += eventData[offset] << 16
			offset += 1
			event_time += eventData[offset] << 8
			offset += 1
			event_time += eventData[offset]
			offset += 1

			timestring = datetime.datetime.fromtimestamp(event_time).strftime('%d.%m.%Y %H:%M:%S')

			data['events'].append({'mode':event_mode, 'time':event_time, 'timestring':timestring})


	return data


app = Flask(__name__)

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/config')
def config():
	now = time.time()
	timestring = datetime.datetime.fromtimestamp(now).strftime('%d.%m.%Y %H:%M:%S')
	return render_template('config.html', time=timestring)

@app.route('/time')
def do_time():
	return render_template('time.html')


# AJAX functions follow

@app.route('/config/settime')
def settime():				# Sets the server time to the device
	ret = do_command(120)		# 120 = Set time
	return makeJSONreply(ret)

@app.route('/status')
def status():
	ret = do_command(100)		# 100 = Status query
	return makeJSONreply(ret, True)

@app.route('/toggle/<relay>')
def toggle(relay):
	ret = do_command(3)		# 3 = Toggle relay 1
	return makeJSONreply(ret)

@app.route('/time/add')
def add_time():
	time1string = request.args.get('startdate') + ' ' + request.args.get('starttime')
	time2string = request.args.get('stopdate') + ' ' + request.args.get('stoptime')
	try:
		time1 = int(time.mktime(datetime.datetime.strptime(time1string, "%Y-%m-%d %H:%M").timetuple()))
		time2 = int(time.mktime(datetime.datetime.strptime(time2string, "%Y-%m-%d %H:%M").timetuple()))
	except:
		return makeJSONerror()

	ret = do_command(20, time1, time2)		# 20 = Relay 1 timing programming
	return makeJSONreply(ret)

@app.route('/time/update')
def update_time():
	ret = do_command(250)		# 250 is a server special command to request info on all scheduled events
	print ret
	return makeJSONreply(ret)

@app.route('/time/clear')
def clear_time():
	ret = do_command(30)		# 30 = Clear all timed events (clear scheduler)
	return makeJSONreply(ret)


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')

