#define libds.a

OBJECTSDIRS = ../advancedC/Vector/genVec.o ../advancedC/Double_Iter/double.o ../advancedC/BST/binary.o ../advancedC/Hash/hashmap.o  ../advancedC/Heap/heap.o ../advancedC/logger/log.o ../advancedC/logger/config.o ../advancedC/scheduler/periodic.o ../advancedC/scheduler/tasks.o ../advancedC/scheduler/time.o

$(LIB_PATH)libds.so.1.0: $(OBJECTSDIRS) 
	gcc -shared -Wl,-soname,libds.so.1 -o libds.so.1.0 $(OBJECTSDIRS) 
	ln -sf libperiods.so.1.0 $(LIB_PATH)libds.so.1
	ln -sf libds.so.1.0 $(LIB_PATH)libds.so
	mv libds.so.1.0 $(LIB_PATH)


 

../advancedC/Vector/genVec.o:
	cd ../advancedC/Vector/ && $(MAKE) vector.o
	
../advancedC/Double_Iter/double.o:
	cd ../advancedC/Double_Iter/ && $(MAKE) double.o
	
 ../advancedC/BST/binary.o:
	cd ../advancedC/BST/ && $(MAKE) binary.o
	
../advancedC/Hash/hashmap.o :
	cd ../advancedC/Hash/ && $(MAKE) hashmap.o
	
../advancedC/Heap/heap.o:
	cd ../advancedC/Heap/ && $(MAKE) heap.o
	
../advancedC/logger/log.o:
	cd ../advancedC/logger/ && $(MAKE) log.o
	
../advancedC/logger/config.o:
	cd../advancedC/logger/ && $(MAKE) config.o
	
../advancedC/scheduler/periodic.o:
	cd ../advancedC/scheduler/ && $(MAKE) periodic.o
	
../advancedC/scheduler/tasks.o:
	cd ../advancedC/scheduler/ && $(MAKE) tasks.o

../advancedC/scheduler/time.o:
	cd ../advancedC/scheduler/ && $(MAKE) time.o
	
#clean:
#	rm -f libds.a 
#	cd ../ds/vector/ && $(MAKE) clean
#	cd ../ds/list/ && $(MAKE) clean
#	cd ../ds/queue_fixed/ && $(MAKE) clean
#	cd ../ds/queue/ && $(MAKE) clean
#	cd ../ds/stack/ && $(MAKE) clean
#	cd ../ds/tree/ && $(MAKE) clean
#	cd ../ds/heap/ && $(MAKE) clean
#	cd ../ds/hashmap/ && $(MAKE) clean
	
	
