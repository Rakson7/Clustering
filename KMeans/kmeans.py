import numpy as np
import matplotlib.pyplot as plt
import random
import sys

#Plotting the graph if Data is 2d
def Two_D_plot(data_points,new_k_mean_pts,data_points_clid):
	plt.figure(num=None, figsize=(14, 14))
	plt.scatter(data_points[:,0],data_points[:,1], c=data_points_clid,marker='.',alpha=0.75,s=1)
	plt.scatter(new_k_mean_pts[:,0],new_k_mean_pts[:,1],c='b',marker='D',alpha=1,s=50)	
	plt.draw()

def write_to_file(k,data_points,data_points_clid):
	point_id=np.array(range(np.size(data_points,0)))
	outfile=open('kmeans.txt','wb')
	for i in range(k):
	    same_clus=point_id[data_points_clid==i]
	    header=str.encode('#'+str(i)+'\n')
	    outfile.write(header)
	    np.savetxt(outfile,same_clus,fmt='%s')    
	outfile.close()

def main():
	k=int(sys.argv[1])
	file_name=sys.argv[2]
	plot_flag=0
	if len(sys.argv)==4: plot_flag=int(sys.argv[3])
	
	data_points=np.genfromtxt(file_name)
	data_points_clid=np.zeros(len(data_points))-1
	
	
	#Assigning Initial Means Randomly
	rand_k_pos=random.sample(range(len(data_points)) , k )	
	new_k_mean_pts=data_points[rand_k_pos,:]
	old_k_mean_pts=np.copy(new_k_mean_pts)*0

	
	#Implementation of KMEANS
	itr=1
	
	while( itr<=1000 and not(np.array_equal(old_k_mean_pts,new_k_mean_pts))  ):
		itr+=1
		data_points_clid= np.argmin([np.linalg.norm(data_points- kth_mean  , axis=1)  for kth_mean in new_k_mean_pts],axis=0)

		old_k_mean_pts=np.copy(new_k_mean_pts)

		#Updating the New Means 
		for i in range(k):
		  same_clus=data_points[data_points_clid==i]
		  new_k_mean_pts[i]=np.mean(same_clus,axis=0)   
	
	
	#Saving to kmeans.txt
	write_to_file(k,data_points,data_points_clid)		

	#Plotting 2D plot
	if plot_flag and np.size(data_points,1)==2:
		Two_D_plot(data_points,new_k_mean_pts,data_points_clid)
		plt.show()
	

if __name__=='__main__':
	main()
		      

	
