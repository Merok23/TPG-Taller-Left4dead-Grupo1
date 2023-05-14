
class Action {
    public:
        virtual void execute() = 0; //Como no es instanciable, no hace falta constructor.
        virtual ~Action();
};
