all : submission

submission : submission.o
	g++ -o submission submission.o
    
submission.o : submission.cpp
	g++ -c submission.cpp