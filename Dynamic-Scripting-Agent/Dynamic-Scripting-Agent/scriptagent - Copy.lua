--Dynamic scripting agent


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

--not sure if these variables are needed here in lua..
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

	if marioState[5] == 0 then
		isMarioAbleToShoot = false
	else
		isMarioAbleToShoot = true
	end
	
	if marioState[6] == 0 then
		isMarioCarrying = false
	else
		isMarioCarrying = true
	end
	
	--not sure if these are needed here in lua...
	killsByTotal = marioState[7]
	killsByFire = marioState[8]
	killsByStomp = marioState[9]
	killeByShell = marioState[10]
	
	
end

function getAction()
	newAction = not isMarioOnGround or isMarioAbleToJump
	
	if newAction == true then
		action[4] = 1
	else
		action[4] = 0
	end
	
	if isMarioAbleToShoot == true then
		action[5] = 1
	else
		action[5] = 0
	end
end
