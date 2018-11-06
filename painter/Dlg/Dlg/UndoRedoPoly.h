#pragma once
class UndoRedoPoly {
public:
	virtual void perform() = 0;
	virtual void rollback() = 0;
};