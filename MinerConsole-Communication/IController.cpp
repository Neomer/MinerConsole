#include "IController.h"

IController::IController(IController *parent) :
    QObject(parent)
{

}

void IController::subscribe(QString path, IControllerPoint *point)
{
    _map[path] = point;
}

void IController::dispatch(QString path, QString action, QVariant data)
{
    LOG_TRACE << path << action << data;

    if (_map.contains(path))
    {
        _map[path]->dispatch(action, data);
    }
}
