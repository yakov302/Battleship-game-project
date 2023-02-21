SRC_DIR = .
INC_DIR = ../inc

CXX = g++
CC = $(CXX)
WARNINGS = -pedantic
DEBUG = -g3
CXX_STD = c++17
LDLIBS  =  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD) $(LDLIBS)
CPPFLAGS = -I$(INC_DIR)

TARGET = main
OBJS = ./main.o ./main.o ./ship.o ./screen.o ./matrix.o ./ships_manager.o ./image_manager.o
$(TARGET):$(OBJS)

main.o: main.cpp $(INC_DIR)/screen.hpp 
	$(CC) $(CXXFLAGS) -c main.cpp

ship.o: ship.cpp $(INC_DIR)/shape.hpp 
	$(CC) $(CXXFLAGS) -c ship.cpp

screen.o: screen.cpp  $(INC_DIR)/ship.hpp  $(INC_DIR)/image_manager.hpp 
	$(CC) $(CXXFLAGS) -c screen.cpp

matrix.o: matrix.cpp  $(INC_DIR)/matrix.hpp 
	$(CC) $(CXXFLAGS) -c matrix.cpp

ships_manager.o: ships_manager.cpp  $(INC_DIR)/ships_manager.hpp 
	$(CC) $(CXXFLAGS) -c ships_manager.cpp

image_manager.o: image_manager.cpp  $(INC_DIR)/image_manager.hpp 
	$(CC) $(CXXFLAGS) -c image_manager.cpp

vala: $(TARGET)
	valgrind --log-file=V1.log ./$(TARGET)
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./$(TARGET) 
   
check: $(TARGET)
	./$(TARGET) -v
	
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: check clean