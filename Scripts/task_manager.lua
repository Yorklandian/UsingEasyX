---@class Task
---@field name string @ task name
---@field thread Thread @ task coroutine
---@field async AsyncAction @��װ����Ҫִ�еĺ���
--- 
---@class TaskManager
---@field _waits Task[]
---@field _readys Task[]
---@field launch fun(task:any)
---@field update fun():boolean
---@field start fun()
---
---@class AsyncAction
---@field __async boolean @�Ƿ�Ҫ�첽
---@field respond fun(requestVal):any @����ִ�еĺ�����
---@field isReady fun():boolean
---@field requestVal any @���룿
---@field respondVal any @���
---
---@type TaskManager
local _gTaskManager = nil

---@return TaskManager
local function getTaskManager()
    if _gTaskManager ~= nil then return _gTaskManager; end

    _gTaskManager = {}
    _gTaskManager._waits = {}
    _gTaskManager._readys = {}


    function _gTaskManager.launch(action, name)
        ---@type Task
        local task = {}
        task.name = name or "unknown"
        task.thread = coroutine.create(action)
        table.insert(_gTaskManager._waits, task);
    end

    function _gTaskManager.start()
        while true do 
            --��ѭ����updateΪtrueʱ������task������ɣ�����ѭ��
            if _gTaskManager.update() then 
                break 
            end 
        end
    end


    function _gTaskManager.update()
        local waits = _gTaskManager._waits;
        _gTaskManager._waits = {}
        
        --����waits���������readysβ��task.async�仯��
        for _, task in ipairs(waits) do
            if not task.async then --�����첽�ģ�ֱ��ready
                table.insert(_gTaskManager._readys, task);
            elseif task.async.isReady() then --��Ҫ�첽����isReadyΪtrue�ģ�ready
                table.insert(_gTaskManager._readys, task);
            else
                table.insert(_gTaskManager._waits, task);--��Ҫ�첽��isReadyΪfalse�ģ�����wait
            end
        end

        local readys = _gTaskManager._readys;
        _gTaskManager._readys = {}

        ---����readys
        for _, task in ipairs(readys) do
            local rsp = nil;

            if task.async then 
                rsp = task.async.respondVal
            end
            --ret�õ�����yield��ֵ�򷵻�ֵ
            local succ, ret = coroutine.resume(task.thread, rsp);
            local st = coroutine.status(task.thread)
            if succ then
                if st == 'dead' then
                    print('-----------finish task: ' .. task.name)
                else
                    --δ����������¼���waits��
                    if ret and ret['__async'] == true then
                        task.async = ret;
                        table.insert(_gTaskManager._waits, task);
                    else
                        task.async = nil;
                        table.insert(_gTaskManager._waits, task);
                    end
                end
            else
                --taskʧ��
                print('-----------fail to finish task: ' .. task.name .. '\n' .. ret)
            end
        end
        -- waits��readysΪ�գ�ִ�����
        if #_gTaskManager._waits == 0 and #_gTaskManager._readys == 0 then
            print('-----------all task are finished')
            return true;
        end

        return false;
    end

    return _gTaskManager;
end

---@param last number
---@return AsyncAction
local function wait(last)
    ---@type AsyncAction 
    local waitAction = {}
    waitAction.__async = true--wait����Ҫִ���첽�Ĳ���

    local now = os.clock();
    local till = now + last
    waitAction.isReady = function()--ʱ�䵽֮ǰisReadyΪfalse
        local now = os.clock();
        if till <= now then
            return true
        end
        return false
    end
    coroutine.yield(waitAction)
end

local function myPrint(content)
    print(content)
end

return {
    wait = wait,
    getTaskManager = getTaskManager,
    myPrint=myPrint
}