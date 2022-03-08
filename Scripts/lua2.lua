local tmlib=require('Scripts.task_manager')
local taskManager=tmlib.getTaskManager()
local wait=tmlib.wait
PI = 3.1415926535

local img = MoImage.CreateObject(".\\Resource\\Smile.jpg", 200, 200)
local img2=MoImage.CreateObject(".\\Resource\\Smile.jpg",500, 500)
function task1()
    img:Move(5)
    wait(1)
    img:Turn(PI/3)
    wait(1)
    img:Move(5)
    wait(1)
    img:SlideTo(0,0,0.01)
end

function task2()
    img2:Move(10)
    wait(2)
    img2:Turn(-PI/6)
    wait(0.5)
    img2:SlideTo(0,0,0.01)
end
taskManager.launch(task1,"task1")
taskManager.launch(task2,"task2")
taskManager.start()

--img:SlideTo(0,0,0.01)
--img:Move(5)
--img:Turn(PI/3)