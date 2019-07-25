import numpy as np
import time

class Clusterizator:
    def __init__(self,clusters_count = 1):
        self.clusters_count = clusters_count
    
    def k_mean_pp(self,samples):
        rnd = int(np.random.uniform(0,len(samples),None))
        centroids = [samples[rnd]]
        for _ in range(1,self.clusters_count):
            propobilitys = np.array([self.__distance_to_closest_centroid(sample,centroids)**2 for sample in samples])
            propobilitys /= sum(propobilitys)
            rnd = int(np.random.choice(len(samples),p=propobilitys))
            centroids.append(samples[rnd].copy())
        return self.__k_mean_base(samples,np.array(centroids))
        
    def k_mean(self,samples):
        centroids = samples[:self.clusters_count,:].copy()
        return self.__k_mean_base(samples,centroids)

    def __k_mean_base(self,samples,centroids):
        # init:
        clusters_projection = []
        new_centroids = []
        # main cycle
        while True:
            # step 1: samples projection on clusters
            clusters_projection = np.argmin(self.__euclidean_norm(samples,centroids),axis=0)
            # step 2: new centroids calculating
            new_centroids = [np.mean(samples[mask],axis=0) for mask in [cluster == clusters_projection for cluster in range(self.clusters_count)]]
            # step 3:
            if np.equal(centroids, new_centroids).all():
                break
            centroids = new_centroids
        return clusters_projection

    def __euclidean_norm(self,samples, centroids):
        return np.array([np.sum(np.subtract(samples,centroid)**2,axis=1)**0.5 for centroid in centroids])
    
    def __distance_to_closest_centroid(self,sample,centroids):
        distance_buffer = np.empty(len(centroids))
        for j in range(len(centroids)):
                distance_buffer[j] = np.sqrt(sum((sample - centroids[j])**2))
        return distance_buffer.min()



