vxbuffer = []
vtbuffer = []
vnbuffer = []
isNextGroup = True
InputFileName = "teapot"
OuputFileName = InputFileName + "-new"

print("", end="", file = open(OuputFileName + ".obj", "w"))

for line in open(InputFileName + ".obj", "r"):
	# remove tab, space
	temp = line.replace("\t", " ")
	temp = temp.replace("\n", "")
	temp = temp.replace("  ", " ")
	temp = temp.replace("  ", " ")
	# make it a list
	temp = temp.split(" ")
	# start rebuild obj file
	if  temp[0] == "v":
		if  isNextGroup:
			isNextGroup = False
		findex = 0
		vxbuffer.append(temp[1])
		vxbuffer.append(temp[2])
		vxbuffer.append(temp[3])

	elif temp[0] == "vt":
		vtbuffer.append(temp[1])
		vtbuffer.append(temp[2])
		vtbuffer.append(temp[3])

	elif temp[0] == "f":
		isNextGroup = True
		# ex: cornell-box, [f v1 v2 v3 v4]
		if temp[1].find("/") == -1:
			print("T %f %f %f %f %f %f %f %f %f " % 
			     (float(vxbuffer[int(temp[1])*3+0]), float(vxbuffer[int(temp[1])*3+1]), float(vxbuffer[int(temp[1])*3+2]), 
			      float(vxbuffer[int(temp[2])*3+0]), float(vxbuffer[int(temp[2])*3+1]), float(vxbuffer[int(temp[2])*3+2]),
			      float(vxbuffer[int(temp[3])*3+0]), float(vxbuffer[int(temp[3])*3+1]), float(vxbuffer[int(temp[3])*3+2])),
			      file = open(OuputFileName + ".obj", "a"))
			print("T %f %f %f %f %f %f %f %f %f " % 
			     (float(vxbuffer[int(temp[1])*3+0]), float(vxbuffer[int(temp[1])*3+1]), float(vxbuffer[int(temp[1])*3+2]), 
			      float(vxbuffer[int(temp[3])*3+0]), float(vxbuffer[int(temp[3])*3+1]), float(vxbuffer[int(temp[3])*3+2]),
			      float(vxbuffer[int(temp[4])*3+0]), float(vxbuffer[int(temp[4])*3+1]), float(vxbuffer[int(temp[4])*3+2])),
			      file = open(OuputFileName + ".obj", "a"))
		# ex: teapot, sponza, [f v1/vt1 v2/vt2 v3/vt3 v4/vt4]
		else:
			# f v1/vt1 v2/vt2 v3/vt3 v4/vt4
			tempf = []
			for i in range(1, len(temp) - 1):
				tempf.append(temp[i].split("/")[0])
			# print(tempf, file = open(OuputFileName + ".obj", "a"))

			if len(tempf) == 4:
				print("T %f %f %f %f %f %f %f %f %f 0.725 0.71 0.68" % 
				     (float(vxbuffer[(int(tempf[0])-1)*3+0]), float(vxbuffer[(int(tempf[0])-1)*3+1]), float(vxbuffer[(int(tempf[0])-1)*3+2]), 
				      float(vxbuffer[(int(tempf[1])-1)*3+0]), float(vxbuffer[(int(tempf[1])-1)*3+1]), float(vxbuffer[(int(tempf[1])-1)*3+2]),
				      float(vxbuffer[(int(tempf[2])-1)*3+0]), float(vxbuffer[(int(tempf[2])-1)*3+1]), float(vxbuffer[(int(tempf[2])-1)*3+2])),
				      file = open(OuputFileName + ".obj", "a"))
				print("T %f %f %f %f %f %f %f %f %f 0.725 0.71 0.68" % 
				     (float(vxbuffer[(int(tempf[0])-1)*3+0]), float(vxbuffer[(int(tempf[0])-1)*3+1]), float(vxbuffer[(int(tempf[0])-1)*3+2]), 
				      float(vxbuffer[(int(tempf[2])-1)*3+0]), float(vxbuffer[(int(tempf[2])-1)*3+1]), float(vxbuffer[(int(tempf[2])-1)*3+2]),
				      float(vxbuffer[(int(tempf[3])-1)*3+0]), float(vxbuffer[(int(tempf[3])-1)*3+1]), float(vxbuffer[(int(tempf[3])-1)*3+2])),
				      file = open(OuputFileName + ".obj", "a"))

			# f v1/vt1 v2/vt2 v3/vt3
			elif len(tempf) == 3:
				print("T %f %f %f %f %f %f %f %f %f 0.725 0.71 0.68" % 
				     (float(vxbuffer[(int(tempf[0])-1)*3+0]), float(vxbuffer[(int(tempf[0])-1)*3+1]), float(vxbuffer[(int(tempf[0])-1)*3+2]), 
				      float(vxbuffer[(int(tempf[1])-1)*3+0]), float(vxbuffer[(int(tempf[1])-1)*3+1]), float(vxbuffer[(int(tempf[1])-1)*3+2]),
				      float(vxbuffer[(int(tempf[2])-1)*3+0]), float(vxbuffer[(int(tempf[2])-1)*3+1]), float(vxbuffer[(int(tempf[2])-1)*3+2])),
				      file = open(OuputFileName + ".obj", "a"))