action = {0, 0, 0, 0, 0, 0}
marioState = {}
marioPos = {}
enemyPos = {}
mariomode = 0
marioStatus = 0
isMarioOnGround = false
isMarioAbleToJump = false
isMarioAbleToShoot = false
isMarioCarrying = false

--not sure if these variables are need here in lua..
killsByTotal = 0
killsByFire = 0
killsByStomp = 0
killsByShell = 0



function init()
	action[2] = 1
	action[5] = 1
end

function integrateObservation()

	marioStatus = marioState[1]
	marioMode = marioState[2]
	
	if marioState[3] == 0 then
		isMarioOnGround = false
		else
		isMarioOnGround = true
	end
	
	if marioState[4] == 0 then
		isMarioAbleToJump = false
		else
		isMarioAbleToJump = true
	end
	
	isMarioAbleToShoot = marioState[5]
	isMarioCarrying = marioState[6]
	
	--not sure if these are needed here in lua...
	killsByTotal = marioState[7]
	killsByFire = marioState[8]
	killsByStomp = marioState[9]
	killeByShell = marioState[10]
	
	
end
---m_action.at(3) = !m_isMarioOnGround || m_isMarioAbleToJump;

function getAction()
	newAction = not isMarioOnGround or isMarioAbleToJump
	
	if newAction == true then
		action[4] = 1
	else
		action[4] = 0
	end
	
end
