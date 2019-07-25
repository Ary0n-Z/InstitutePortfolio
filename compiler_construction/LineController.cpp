#include "LineController.h"



LineController::LineController(unique_ptr<ILineReader> lineContainer)
{
	this->lineContainer = std::unique_ptr<ILineReader>(std::move(lineContainer));
	if(this->lineContainer->CanRead())
		line = this->lineContainer->NextLine(); // Preloaded line!
}

LineController::~LineController(){}

char LineController::NextCharWithWrapping(){
	char temp = EMPTY_CHAR;
	if (currentCharIndex != line.size()) {
		temp = line[currentCharIndex];
		++currentCharIndex;
	}
	else {
		if (lineContainer->CanRead()) {
			line = lineContainer->NextLine();
			temp = '\n';
			currentCharIndex=0;
		}//TODO:: Else cant't read!
	}
	return temp;
}
size_t LineController::CurrenIndex() {
	return this->currentCharIndex - 1;
}

size_t LineController::WhatLine() {
	return lineContainer->LineNum()+1;
}

