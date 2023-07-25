#ifndef SERVER_ACTION_CREATE_SOLDIER_IDF_H
#define SERVER_ACTION_CREATE_SOLDIER_IDF_H

#include "action.h"
#include "weapon_idf.h"

class CreateSoldierIdf : public Action {
    private:
        std::string name;
    public:
        /**
         * @brief Constructor de la clase CreateSoldierIdf.
         */
        explicit CreateSoldierIdf(const std::string& name);

        virtual void execute(IdHandler& handler) override;

        ~CreateSoldierIdf() override;
};
#endif
