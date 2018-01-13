#!/bin/bash
CXX = g++
CXXFLAGS = -Wall -MMD
SRCS = cc3k.cpp common.cpp object.cpp character.cpp player.cpp knight.cpp wizard.cpp samurai.cpp item.cpp potion.cpp treasure.cpp gold_pile.cpp dragon_hoard.cpp rh.cpp ph.cpp wa.cpp wd.cpp ba.cpp bd.cpp cell.cpp factory.cpp canvas.cpp display.cpp
OBJS = $(SRCS: .cpp=.o)
EXEC = cc3k

$(EXEC): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

cc3k.o: common.h object.h character.h player.h knight.h wizard.h samurai.h item.h potion.h treasure.h gold_pile.h dragon_hoard.h rh.h ph.h wa.h wd.h ba.h bd.h cell.h factory.h canvas.h cc3k.h display.h

.cpp.o: $(CXX) $(CXXFLAGS) -c $< -o $@

clean:  rm *.o $(EXEC)

