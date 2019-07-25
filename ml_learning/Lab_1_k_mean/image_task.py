import numpy as np
from pandas import read_csv
import clusterization
import matplotlib.pyplot as plt
from scipy import misc
import imageio
import time

img = imageio.imread('img.png')
samples = np.reshape(img, (-1,3))
clusters_count = 3
clust = clusterization.Clusterizator(clusters_count)
start = time.time()
print("START:")
clusters = clust.k_mean_pp(samples)
print('STOP, time = {0}'.format(time.time() - start))
centroids = np.zeros((clusters_count,3))
counter_buffer = np.zeros(clusters_count)
centroids = [np.mean(samples[mask],axis=0) for mask in [cluster == clusters for cluster in range(clusters_count)]]
for i in range(len(samples)):
    samples[i] = centroids[clusters[i]]
plt.imshow(img)
plt.show()