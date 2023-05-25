#include "action.h"
#include "weapon_idf.h"

class CreateSoldierIdf : public Action {
    public:
        CreateSoldierIdf();
        virtual void execute(IdHandler& handler) override;

        ~CreateSoldierIdf() override;
};
