local function wait(seconds)
    local time = seconds or 1
    local start = os.time()
    repeat until os.time() == start + time
end
PI = 3.1415926535

print("hello?")
local img=MoImage.CreateObject(".\\Resource\\Smile.jpg", 200, 200)
img:Move(5)