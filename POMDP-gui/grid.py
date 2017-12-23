#!/usr/bin/python
from Tkinter import *
from PIL import Image, ImageTk
import re
import sys

# print "This is the name of the script: ", sys.argv[0]
# print "Number of arguments: ", len(sys.argv)
# print "The arguments are: " , str(sys.argv)

VERBOSE = False
STATE = "INIT"
file_name = ""
next_arg_file = False
for arg in sys.argv[1:]:
	print arg
	if next_arg_file:
		file_name = arg
	else:
		if "v" in arg:
			VERBOSE = True
		if "f" in arg:
			next_arg_file = True
		# file_name = arg


class App:
	def __init__(self, master):

		self.frame = Frame(master, bg='grey', width=1024, height=50)
		self.frame.pack()

		self.w = Canvas(master, width = 512, height = 384, background = "black")
		self.w.pack(side = LEFT)
		self.w2 = Canvas(master, width = 512, height = 384, background = "black")
		self.w2.pack(side = RIGHT)

		self.button1 = Button(self.frame, text='Step', command=self.next_state)
		self.button1.pack(side=RIGHT)

		# variables for lanes
		lane_width = 20
		num_center_lines = 8
		
		stipple_color_out = "gray75"
		stipple_color_in = "gray50"
		fill_in = "black"
		activefill_in = "orange"
		fill_out = "green"

		# grid rectangles state
		self.grid_left  = self.w.create_rectangle(  0,0,128,384, fill = fill_out, stipple = stipple_color_out)
		self.grid_right = self.w.create_rectangle(384,0,512,384, fill = fill_out, stipple = stipple_color_out)
		self.grid_0 = self.w.create_rectangle(128,  0,256,128, fill = fill_in, activefill = activefill_in , stipple = stipple_color_in)
		self.grid_1 = self.w.create_rectangle(256,  0,384,128, fill = fill_in, activefill = activefill_in , stipple = stipple_color_in)
		self.grid_2 = self.w.create_rectangle(128,128,256,256, fill = fill_in, activefill = activefill_in , stipple = stipple_color_in)
		self.grid_3 = self.w.create_rectangle(256,128,384,256, fill = fill_in, activefill = activefill_in , stipple = stipple_color_in)
		self.grid_4 = self.w.create_rectangle(128,256,256,384, fill = fill_in, activefill = activefill_in , stipple = stipple_color_in)
		self.grid_5 = self.w.create_rectangle(256,256,384,384, fill = fill_in, activefill = activefill_in , stipple = stipple_color_in)
		
		# grid rectangles observation
		self.grid_obs_left  = self.w2.create_rectangle(  0,0,128,384, fill = fill_out, stipple = stipple_color_out)
		self.grid_obs_right = self.w2.create_rectangle(384,0,512,384, fill = fill_out, stipple = stipple_color_out)
		self.grid_obs_0 = self.w2.create_rectangle(128,  0,256,128, fill = fill_in, activefill = activefill_in, stipple = stipple_color_in)
		self.grid_obs_1 = self.w2.create_rectangle(256,  0,384,128, fill = fill_in, activefill = activefill_in, stipple = stipple_color_in)
		self.grid_obs_2 = self.w2.create_rectangle(128,128,256,256, fill = fill_in, activefill = activefill_in, stipple = stipple_color_in)
		self.grid_obs_3 = self.w2.create_rectangle(256,128,384,256, fill = fill_in, activefill = activefill_in, stipple = stipple_color_in)
		self.grid_obs_4 = self.w2.create_rectangle(128,256,256,384, fill = fill_in, activefill = activefill_in, stipple = stipple_color_in)
		self.grid_obs_5 = self.w2.create_rectangle(256,256,384,384, fill = fill_in, activefill = activefill_in, stipple = stipple_color_in)

		# left lane
		self.w.create_rectangle(128 - lane_width /2 ,0,128 + lane_width /2 ,385, fill = "white")
		self.w2.create_rectangle(128 - lane_width /2 ,0,128 + lane_width /2 ,385, fill = "white")
		
		# right lane 
		self.w.create_rectangle(384 - lane_width /2, 0, 384 + lane_width /2, 384, fill = "white")
		self.w2.create_rectangle(384 - lane_width /2, 0, 384 + lane_width /2, 384, fill = "white")
		
		# central lines
		for i in xrange(0,num_center_lines):
			self.w.create_rectangle(256 - lane_width /4, i*384/num_center_lines, 256 +  lane_width / 4, i*384/num_center_lines + 25, fill = "white")
			self.w2.create_rectangle(256 - lane_width /4, i*384/num_center_lines, 256 +  lane_width / 4, i*384/num_center_lines + 25, fill = "white")

		# arrows left
		self.arrow_ru = self.w.create_line(320,320,320,256, arrow = LAST, width = 3, fill = "red", state = HIDDEN )
		self.arrow_rl = self.w.create_line(320,320,384,320, arrow = LAST, width = 3, fill = "red", state = HIDDEN )
		self.arrow_rr = self.w.create_line(320,320,256,320, arrow = LAST, width = 3, fill = "red", state = HIDDEN )

		# arrow right
		self.arrow_lu = self.w.create_line(192,320,192,256, arrow = LAST, width = 3, fill = "red", state = HIDDEN )
		self.arrow_ll = self.w.create_line(192,320,256,320, arrow = LAST, width = 3, fill = "red", state = HIDDEN )
		self.arrow_lr = self.w.create_line(192,320,128,320, arrow = LAST, width = 3, fill = "red", state = HIDDEN )
		
		# autonomos image
		self.image = Image.open("media/autonomos_alpha.png")
		self.image = self.image.resize((34, 64), Image.ANTIALIAS) 
		self.photo = ImageTk.PhotoImage(self.image)
		self.autonomos_image = self.w.create_image(320, 320, image = self.photo)

		# autonomos image obs
		self.autonomos_image_obs = self.w2.create_image(320, 320, image = self.photo)

		# labels
		self.w.create_rectangle(222, 360, 290, 390, fill = "white")
		self.label_w = self.w.create_text((256, 375), text="States", fill = "red", font = ("Helvetica", 16))

		self.w2.create_rectangle(187, 360, 322, 390, fill = "white")
		self.label_w2 = self.w2.create_text((256, 375), text="Observations", fill = "red", font = ("Helvetica", 16))

	def next_state(self):
		global STATE
		STATE = "STEP"

	def test(self, master, case, action, observation):

		# 0 <- black
		# 1 <- yellow
		# 2 <- red
		edos_matrix = [ 				
					#0,1,2,3,4,5 		
					[0,0,0,0,0,0], #0
					[1,0,0,0,0,0], #1
					[0,0,1,0,0,0], #2
					[0,0,0,0,1,0], #3
					[0,1,0,0,0,0], #4
					[0,0,0,1,0,0], #5
					[1,1,0,0,0,0], #6
					[1,0,0,1,0,0], #7
					[0,1,1,0,0,0], #8
					[0,1,0,0,1,0], #9
					[0,0,1,1,0,0], #10
					[0,0,0,1,1,0], #11
					[0,0,0,0,0,0], #12
					[0,1,0,0,0,0], #13
					[0,0,0,1,0,0], #14
					[0,0,0,0,0,1], #15
					[1,0,0,0,0,0], #16
					[0,0,1,0,0,0], #17
					[1,1,0,0,0,0], #18
					[0,1,1,0,0,0], #19
					[1,0,0,1,0,0], #20
					[1,0,0,0,0,1], #21
					[0,0,1,1,0,0], #22
					[0,0,1,0,0,1], #23
					[2,2,2,2,2,2] #24
					]
		# [,,,,,]

		gridx_arr = [
					self.grid_0,
					self.grid_1,
					self.grid_2,
					self.grid_3,
					self.grid_4,
					self.grid_5
					]
		gridx_arr_obs = [
					self.grid_obs_0,
					self.grid_obs_1,
					self.grid_obs_2,
					self.grid_obs_3,
					self.grid_obs_4,
					self.grid_obs_5
					]
		arrow_arr = [
					self.arrow_ru,
					self.arrow_rl,
					self.arrow_rr,
					self.arrow_lu,
					self.arrow_ll,
					self.arrow_lr,
					]	
		color_map = \
			{
				0 : "black",
				1 : "yellow",
				2 : "red"
			}
		edos_map = \
			{
				"f_r"   : 0  ,
				"tl_r"  : 1  ,
				"ml_r"  : 2  ,
				"sl_r"  : 3  ,
				"tr_r"  : 4  ,
				"mr_r"  : 5  ,
				"xt_r"  : 6  ,
				"xtm_r" : 7  ,
				"xmt_r" : 8  ,
				"xst_r" : 9  ,
				"xm_r"  : 10 ,
				"xsm_r" : 11 ,
				"f_l"   : 12 ,
				"tr_l"  : 13 ,
				"mr_l"  : 14 ,
				"sr_l"  : 15 ,
				"tl_l"  : 16 ,
				"ml_l"  : 17 ,
				"xt_l"  : 18 ,
				"xmt_l" : 19 ,
				"xtm_l" : 20 ,
				"xts_l" : 21 ,
				"xm_l"  : 22 ,
				"xms_l" : 23 ,
				"CRASH" : 24 
			}

		action_map = \
			{
				"rUp"   : 0,
				"rRight": 1,
				"rLeft" : 2,
				"lUp"   : 3,
				"lRight": 4,
				"lLeft" : 5,
				"HUp"   : 6,
				"HRight": 6,
				"HLeft" : 6,
				"HStop" : 6,
				"lStop" : 6,
				"rStop" : 6
			}
		action_map.setdefault(6)
		action_arr = \
			[
				[NORMAL, HIDDEN, HIDDEN, HIDDEN, HIDDEN, HIDDEN],
				[HIDDEN, NORMAL, HIDDEN, HIDDEN, HIDDEN, HIDDEN],
				[HIDDEN, HIDDEN, NORMAL, HIDDEN, HIDDEN, HIDDEN],
				[HIDDEN, HIDDEN, HIDDEN, NORMAL, HIDDEN, HIDDEN],
				[HIDDEN, HIDDEN, HIDDEN, HIDDEN, NORMAL, HIDDEN],
				[HIDDEN, HIDDEN, HIDDEN, HIDDEN, HIDDEN, NORMAL],
				[HIDDEN, HIDDEN, HIDDEN, HIDDEN, HIDDEN, HIDDEN],
			]

		colors_arr = edos_matrix[ edos_map[case] ]
		colors_arr_obs = edos_matrix[ edos_map[observation] ]
		
		for grid, color in zip(gridx_arr, colors_arr):
			self.w.itemconfig(grid, fill=color_map[color])

		for grid, color in zip(gridx_arr_obs, colors_arr_obs):
			self.w2.itemconfig(grid, fill=color_map[color])

		act = action_arr[ action_map[ (case[-1] + action) ] ]

		for arrow, arr in zip(arrow_arr, act):
			self.w.itemconfig(arrow, state = arr)

		if case[-1] == "r":
			self.w.coords(self.autonomos_image, 320,320)
			self.w2.coords(self.autonomos_image_obs, 320,320)
		elif case[-1] == "l":
			self.w.coords(self.autonomos_image, 192,320)
			self.w2.coords(self.autonomos_image_obs, 192,320)
		elif case == "CRASH":
			self.w.coords(self.autonomos_image, 256,320)
			self.w2.coords(self.autonomos_image_obs, 256,320)
		
master = Tk()

img = PhotoImage(file="media/icon.png")
scale_w = 64/1744
scale_h = 34/3334
img = img.subsample(32)
master.tk.call('wm', 'iconphoto', master._w, img)



app = App(master)
master.title("AutoNOMOS GUI")
file_obj = open(file_name, "r")

master.update()

case = ""

while 1:
	if STATE == "INIT":
		print STATE if VERBOSE else ""
		line = file_obj.readline()
		while line[0] != "#":
			line = file_obj.readline()
		STATE = "EDO_INI"

	if STATE == "EDO_INI":
		print STATE if VERBOSE else ""
		line = file_obj.readline()
		line = file_obj.readline()
		case = re.search(':(.+?)\]', line).group(0)
		STATE = "STEP"
	
	if STATE == "STEP":
		print STATE if VERBOSE else ""
		while "Action" not in line:
			line = file_obj.readline()
		action = line.split(':')[1].rstrip() #re.search(':(.+?)(.*)', line).group(1)
		line = file_obj.readline()
		line = file_obj.readline()
		case = re.search(':(.+?)\]', line).group(1)	
		line = file_obj.readline()
		observation = re.search(':(.+?)\]', line).group(1)
		print "action:", action,"\tcase:", case,"\tobservation:", observation
		STATE = "IDLE"

	if STATE == "IDLE":
		pass
		
	App.test(app, master, case, action, observation)
	master.update_idletasks()
	master.update()


























