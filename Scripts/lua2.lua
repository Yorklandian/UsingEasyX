local tmlib=require('Scripts.task_manager')
local taskManager=tmlib.getTaskManager()
local wait=tmlib.wait
PI = 3.1415926535

local img=MoImage.CreateObject(".\\Resource\\Smile.jpg", 200, 200)
function task()
    img:Move(5)
    wait(1)
    img:Turn(PI/3)
    wait(1)
    img:Move(5)
end

taskManager.launch(task,"task")
taskManager.start()

--img:SlideTo(0,0,0.01)
--img:Move(5)
--img:Turn(PI/3)