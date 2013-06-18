#ifndef MENUBUTTON_H
#define MENUBUTTON_H


class MenuButton
{
    public:
        int x, y;
        int width, height;
        int stateOfButton;
        char * nameOfButton;
        void (*onClickFunction)(int);

        MenuButton();
        void New();
    protected:
    private:
};

#endif // MENUBUTTON_H
