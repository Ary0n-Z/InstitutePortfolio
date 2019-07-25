import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from pandas import read_csv
from clusterization import Clusterizator

#read data
df = read_csv('iris.csv', header=None)
samples = df.iloc[:,:4].values
#k-mean
cluster_count = 3
cl = Clusterizator(cluster_count)
df['clusters'] = cl.k_mean_pp(samples)
#clusters_projection = cl.k_mean(samples,Clusterizator.euclidean_norm)
#x = data_frame.iloc[:,0].values.ravel()
#y = data_frame.iloc[:,2].values.ravel()
#visualisation
sns.pairplot(df,vars=[0,2],kind="scatter",hue='clusters',height=3)
plt.show()

import numpy as np

a1=np.array([[1,1],[2,2]])
a2=np.array([4,4])
