local function wait(seconds)
    local time = seconds or 1
    local start = os.time()
    repeat until os.time() == start + time
end

 PI = 3.1415926

 wait(1)
local objId = CreateObject(".\\Resource\\Smile.jpg", 200, 200)
wait(1)
Move(objId,5)
wait(1)
Turn(objId,PI/3)
wait(1)
Move(objId,10)
wait(1)
Turn(objId,PI/3)
wait(1)
Move(objId,6)
wait(1)
SlideTo(objId,0,0,0.01)


