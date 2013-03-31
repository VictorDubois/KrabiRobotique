#ifndef LOWLEVELACTION_H_INCLUDED
#define LOWLEVELACTION_H_INCLUDED

class LowLevelAction {

public:
    LowLevelAction(int status = 0);
    virtual ~LowLevelAction();
	/**
	 * launches the action, answers false if it's not finished, true elseway
	 */
	virtual bool update() = 0;

private:
	/**
	 * used for internal status managing. Can be used to count the number of calls to update.
	 */
	int status;
};
#endif
