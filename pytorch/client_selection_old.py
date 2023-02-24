import sys
import time
import matplotlib.pyplot as plt
import numpy as np
import skfuzzy as fuzz
from skfuzzy import control as ctrl
import pandas as pd
import os
from matplotlib import rcParams
rcParams['font.family']='DejaVu Serif'
rcParams['font.size']=18



sampleQuantity = ctrl.Antecedent(np.arange(0, 3901, 1), 'sampleQuantity')

availableThroughput = ctrl.Antecedent(np.arange(0, 1300, 2), 'availableThroughput')

computationalCapability = ctrl.Antecedent(np.arange(1, 21, 0.1), 'computationalCapability')

Loss = ctrl.Antecedent(np.arange(0, 3, 0.1), 'Loss')

Score = ctrl.Consequent(np.arange(0, 81, 1), 'Score')

# Auto-membership function population is possible with .automf(3, 5, or 7)
sampleQuantity.automf(3)
availableThroughput.automf(3)
computationalCapability.automf(3)
Loss.automf(3)


sampleQuantity['poor'] = fuzz.gaussmf(sampleQuantity.universe, 100, 1500)
sampleQuantity['average'] = fuzz.gaussmf(sampleQuantity.universe, 2000, 1500)
sampleQuantity['good'] = fuzz.gaussmf(sampleQuantity.universe, 3800, 1500)

# availableThroughput 中最大值为164，平均值为39
availableThroughput['poor'] = fuzz.gaussmf(availableThroughput.universe, 0, 100)
availableThroughput['average'] = fuzz.gaussmf(availableThroughput.universe, 303, 100)
availableThroughput['good'] = fuzz.gaussmf(availableThroughput.universe, 1300, 500)

computationalCapability['good'] = fuzz.gaussmf(computationalCapability.universe, 1, 5)
computationalCapability['average'] = fuzz.gaussmf(computationalCapability.universe, 11, 5)
computationalCapability['poor'] = fuzz.gaussmf(computationalCapability.universe, 20, 5)

Loss['poor'] = fuzz.gaussmf(Loss.universe, 0.5, 0.3)
Loss['average'] = fuzz.gaussmf(Loss.universe, 1.5, 0.3)
Loss['good'] = fuzz.gaussmf(Loss.universe, 2.2, 0.3)

Score['L0'] = fuzz.gaussmf(Score.universe, 0, 5)
Score['L1'] = fuzz.gaussmf(Score.universe, 10, 5)
Score['L2'] = fuzz.gaussmf(Score.universe, 20, 5)
Score['L3'] = fuzz.gaussmf(Score.universe, 30, 5)
Score['L4'] = fuzz.gaussmf(Score.universe, 40, 5)
Score['L5'] = fuzz.gaussmf(Score.universe, 50, 5)
Score['L6'] = fuzz.gaussmf(Score.universe, 60, 5)
Score['L7'] = fuzz.gaussmf(Score.universe, 70, 5)
Score['L8'] = fuzz.gaussmf(Score.universe, 80, 5)
# Score['L9'] = fuzz.trimf(Score.universe, [80, 90, 90])
#  Score['L9'] = fuzz.trimf(Score.universe, [80, 90, 100])
# Score['L10'] = fuzz.trimf(Score.universe, [90, 100, 100])
# You can see how these look with .view()

#sampleQuantity['good'].view()
#availableThroughput['good'].view()
#computationalCapability['good'].view()
#Loss['good'].view()
#Score.view()
#plt.tight_layout()
#plt.show()
#time.sleep(100)
#sys.exit()


###################  RULE  #######################
# rule1 = ctrl.Rule(sampleQuantity['poor'] & availableThroughput['poor'], Score['poor'])
rule1 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['good']&Loss['good'],Score['L8'])
rule2 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['good']&Loss['good'],Score['L7'])
rule3 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['good']&Loss['good'],Score['L6'])
rule4 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['good']&Loss['good'],Score['L7'])
rule5 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['good']&Loss['good'],Score['L6'])
rule6 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['good']&Loss['good'],Score['L5'])
rule7 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['good']&Loss['good'],Score['L6'])
rule8 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['good']&Loss['good'],Score['L5'])
rule9 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['good']&Loss['good'],Score['L4'])
rule10 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['average']&Loss['good'],Score['L7'])
rule11 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['average']&Loss['good'],Score['L6'])
rule12 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['average']&Loss['good'],Score['L5'])
rule13 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['average']&Loss['good'],Score['L6'])
rule14 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['average']&Loss['good'],Score['L5'])
rule15 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['average']&Loss['good'],Score['L4'])
rule16 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['average']&Loss['good'],Score['L5'])
rule17 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['average']&Loss['good'],Score['L4'])
rule18 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['average']&Loss['good'],Score['L3'])
rule19 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['poor']&Loss['good'],Score['L6'])
rule20 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['poor']&Loss['good'],Score['L5'])
rule21 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['poor']&Loss['good'],Score['L4'])
rule22 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['poor']&Loss['good'],Score['L5'])
rule23 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['poor']&Loss['good'],Score['L4'])
rule24 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['poor']&Loss['good'],Score['L3'])
rule25 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['poor']&Loss['good'],Score['L4'])
rule26 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['poor']&Loss['good'],Score['L3'])
rule27 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['poor']&Loss['good'],Score['L2'])
rule28 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['good']&Loss['average'],Score['L6'])
rule29 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['good']&Loss['average'],Score['L5'])
rule30 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['good']&Loss['average'],Score['L4'])
rule31 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['good']&Loss['average'],Score['L5'])
rule32 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['good']&Loss['average'],Score['L4'])
rule33 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['good']&Loss['average'],Score['L3'])
rule34 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['good']&Loss['average'],Score['L4'])
rule35 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['good']&Loss['average'],Score['L3'])
rule36 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['good']&Loss['average'],Score['L2'])
rule37 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['average']&Loss['average'],Score['L5'])
rule38 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['average']&Loss['average'],Score['L4'])
rule39 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['average']&Loss['average'],Score['L3'])
rule40 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['average']&Loss['average'],Score['L4'])
rule41 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['average']&Loss['average'],Score['L3'])
rule42 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['average']&Loss['average'],Score['L2'])
rule43 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['average']&Loss['average'],Score['L3'])
rule44 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['average']&Loss['average'],Score['L2'])
rule45 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['average']&Loss['average'],Score['L1'])
rule46 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['poor']&Loss['average'],Score['L4'])
rule47 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['poor']&Loss['average'],Score['L3'])
rule48 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['poor']&Loss['average'],Score['L2'])
rule49 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['poor']&Loss['average'],Score['L3'])
rule50 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['poor']&Loss['average'],Score['L2'])
rule51 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['poor']&Loss['average'],Score['L1'])
rule52 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['poor']&Loss['average'],Score['L2'])
rule53 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['poor']&Loss['average'],Score['L1'])
rule54 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['poor']&Loss['average'],Score['L0'])
rule55 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule56 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule57 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule58 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule59 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule60 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule61 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule62 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule63 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['good']&Loss['poor'],Score['L0'])
rule64 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule65 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule66 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule67 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule68 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule69 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule70 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule71 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule72 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['average']&Loss['poor'],Score['L0'])
rule73 = ctrl.Rule(sampleQuantity['good']&computationalCapability['good']&availableThroughput['poor']&Loss['poor'],Score['L0'])
rule74 = ctrl.Rule(sampleQuantity['average']&computationalCapability['good']&availableThroughput['poor']&Loss['poor'],Score['L0'])
rule75 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['good']&availableThroughput['poor']&Loss['poor'],Score['L0'])
rule76 = ctrl.Rule(sampleQuantity['good']&computationalCapability['average']&availableThroughput['poor']&Loss['poor'],Score['L0'])
rule77 = ctrl.Rule(sampleQuantity['average']&computationalCapability['average']&availableThroughput['poor']&Loss['poor'],Score['L0'])
rule78 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['average']&availableThroughput['poor']&Loss['poor'],Score['L0'])
rule79 = ctrl.Rule(sampleQuantity['good']&computationalCapability['poor']&availableThroughput['poor']&Loss['poor'],Score['L0'])
rule80 = ctrl.Rule(sampleQuantity['average']&computationalCapability['poor']&availableThroughput['poor']&Loss['poor'],Score['L0'])
rule81 = ctrl.Rule(sampleQuantity['poor']&computationalCapability['poor']&availableThroughput['poor']&Loss['poor'],Score['L0'])

# rule2 = ctrl.rule(service['average'], tip['medium'])
# rule3 = ctrl.rule(service['good'] | quality['good'], tip['high'])

# rule1.view()

tipping_ctrl = ctrl.ControlSystem(
	[rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9, rule10,
	 rule11, rule12, rule13, rule14, rule15, rule16, rule17, rule18, rule19,
	 rule20, rule21, rule22, rule23, rule24, rule25, rule26, rule27, rule28,
	 rule29, rule30, rule31, rule32, rule33, rule34, rule35, rule36, rule37,
	 rule38, rule39, rule40, rule41, rule42, rule43, rule44, rule45, rule46,
	 rule47, rule48, rule49, rule50, rule51, rule52, rule53, rule54, rule55,
	 rule56, rule57, rule58, rule59, rule60, rule61, rule62, rule63, rule64,
	 rule65, rule66, rule67, rule68, rule69, rule70, rule71, rule72, rule73,
	 rule74, rule75, rule76, rule77, rule78, rule79, rule80, rule81])

tipping = ctrl.ControlSystemSimulation(tipping_ctrl)

clientINFO = pd.read_csv('/home/narisu/src/TFF/toyota_distributedFL/pytorch/client_information.txt')
clientINFO = clientINFO.values.tolist()
loss = pd.read_csv('/home/narisu/src/TFF/toyota_distributedFL/pytorch/client_loss.txt')
loss = loss.values.tolist()
loss_tmp = []
for i in range(len(loss)):
	 for item in loss[i]:
	      loss_tmp.append(item.split(' '))
loss = loss_tmp

tmp = []
for i in range(len(clientINFO)):
	 for item in clientINFO[i]:
	      a = item.split(' ')

	      a.append(loss[i][1])

	      tmp.append(a)

clientINFO = tmp

information = []
for i in range(len(clientINFO)):
	 
	 if abs(float(clientINFO[i][1]) - 500) < 150:
	       throughput = 1200
	 elif abs(float(clientINFO[i][1]) - 500) < 330:
	       throughput = 600
	 else:
	       throughput = 70
	 information.append([int(clientINFO[i][4]), float(clientINFO[i][3]), throughput, float(clientINFO[i][5])]) 


f = open('/home/narisu/src/TFF/toyota_distributedFL/pytorch/globalINFO.txt', 'w')  
for i in range(len(clientINFO)):
	 # print(information[i][0], ' ', information[i][1], ' ', information[i][2], ' ', information[i][3])
	 tipping.input['sampleQuantity'] = information[i][0]
	 tipping.input['computationalCapability'] = information[i][1]
	 tipping.input['availableThroughput'] = information[i][2]
	 tipping.input['Loss'] = information[i][3]
	 
	 # crunch the numbers
	 tipping.compute()
	 # print(information[i][0], ' ', information[i][1], ' ', information[i][2], ' ', information[i][3], tipping.output['Score'])
	 f.write(str(information[i][0]) + ' ' +
	         str(information[i][1]) + ' ' +
	         str(information[i][2]) + ' ' +
	         str(information[i][3]) + ' ' +
	         str(tipping.output['Score']) + '\n')
	 # print(i, tipping.output['Score'])
f.close()
     
