/*
** EPITECH PROJECT, 2025
** files
** File description:
** COMMAND_HANDLER_CPP
*/

#include "./include/command_handler.hpp"
#include "./include/Error.hpp"

bool CommandBuffer::sendCommand(const std::string& cmd)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_buffer.size() >= 10) {
        throw Error("Full of command, waiting for execution of others command");
        return false;
    }
    _buffer.push(cmd);
    _network.send(cmd);
    _pendingCommand = transfert(cmd);
    return true;
}

std::string CommandBuffer::getResponse()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_buffer.empty())
        return "";
    std::string response = _network.receive();
    std::string sentCmd = _buffer.front();
    _buffer.pop();
    return response;
}

PendingCommand CommandBuffer::transfert(const std::string& cmd)
{
    if (cmd == "Forward")
        return PendingCommand::FORWARD;
    if (cmd == "Left")
        return PendingCommand::LEFT;
    if (cmd == "Right")
        return PendingCommand::RIGHT;
    if (cmd == "Look")
        return PendingCommand::LOOK;
    if (cmd == "Take")
        return PendingCommand::TAKE;
    if (cmd == "Set")
        return PendingCommand::SET;
    if (cmd == "Broadcast")
        return PendingCommand::BROADCAST;
    if (cmd == "Connect_nbr")
        return PendingCommand::CONNECT_NBR;
    if (cmd == "Fork")
        return PendingCommand::FORK;
    if (cmd == "eject")
        return PendingCommand::EJECT;
    if (cmd == "Incantation")
        return PendingCommand::INCANTATION;
    if (cmd == "Inventory")
        return PendingCommand::INVENTORY;
    return PendingCommand::NONE;
}

PendingCommand CommandBuffer::getPendingCommand() const
{
    return _pendingCommand;
}

void CommandBuffer::setPendingCommand(PendingCommand cmd)
{
    _pendingCommand = cmd;
}