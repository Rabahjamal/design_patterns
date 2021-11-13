#ifndef VISITOR_H
#define VISITOR_H

#include <string>
#include <iostream>

namespace Visitor
{

class DLinkRouter;
class TPLinkRouter;

class RouterVisitor
{
public:
    RouterVisitor() = default;

    virtual void visit(DLinkRouter* router) = 0;

    virtual void visit(TPLinkRouter* router) = 0;
};

class Router
{
public:
    Router() = default;

    virtual void accept(RouterVisitor* visitor) = 0;
};

class DLinkRouter : public Router
{
public:
    DLinkRouter() = default;

    void accept(RouterVisitor* visitor)
    {
        visitor->visit(this);
    }
};

class TPLinkRouter : public Router
{
public:
    TPLinkRouter() = default;

    void accept(RouterVisitor* visitor)
    {
        visitor->visit(this);
    }
};

class LinuxConfig : public RouterVisitor
{
public:
    LinuxConfig() = default;

    void visit(DLinkRouter* router)
    {
        std::cout << "DLinkRouter Configuration for Linux complete !!" << std::endl;
    }

    void visit(TPLinkRouter* router)
    {
        std::cout << "TPLinkRouter Configuration for Linux complete !!" << std::endl;
    }
};

class WindowsConfig : public RouterVisitor
{
public:
    WindowsConfig() = default;

    void visit(DLinkRouter* router)
    {
        std::cout << "DLinkRouter Configuration for Windows complete !!" << std::endl;
    }

    void visit(TPLinkRouter* router)
    {
        std::cout << "TPLinkRouter Configuration for Windows complete !!" << std::endl;
    }
};

}

#endif // VISITOR_H
