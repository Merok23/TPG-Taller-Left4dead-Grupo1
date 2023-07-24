#include "creatematch.h"
#include "ui_creatematch.h"

CreateMatch::CreateMatch(QWidget *parent, ChooseSoldier* choose_soldier, 
                        COMMANDS* commands, command_t* create_or_join_command) :
    QDialog(parent),
    ui(new Ui::CreateMatch),
    choose_soldier(choose_soldier)
{
    ui->setupUi(this);
    setWindowTitle(tr("Create match"));


    initial_match_name = ui->match_name_input->toPlainText();
    initial_player_name = ui->player_name_input->toPlainText();

    this->commands = commands;
    this->create_or_join_command = create_or_join_command;
}

CreateMatch::~CreateMatch()
{
    delete ui;
}



void CreateMatch::on_peaceful_clicked()
{
    QString message = "Peaceful mode. \n\nNo enemies will be spawned. Just enjoy a stroll in an apocalyptic setting.";
    ui->mode_description->setText(message);
}


void CreateMatch::on_survival_clicked()
{
    QString message =  "Survival mode. \n\nEnemies will spawn randomly. There is no end, just an endless challenge of endurance.";
    ui->mode_description->setText(message);
}


void CreateMatch::on_clear_the_zone_clicked()
{
    QString message = "Clear the zone mode. \n\nA set number of enemies will spawn. If you and your party defeat all of them, you won.";
    ui->mode_description->setText(message);

}

void CreateMatch::on_cancel_clicked()
{
    emit resetCommand(this->commands, this->create_or_join_command);
    close();
}


void CreateMatch::on_choose_skin_clicked()
{
    //Validating data
    if (ui->match_name_input->toPlainText() == initial_match_name ||
        ui->player_name_input->toPlainText() == initial_player_name) {
        QMessageBox::warning(this, "Creating new match", "Please fill out all fields");
    } else {
        QString game_mode_name;
        QList<QRadioButton *> radioButtons = ui->game_mode_box->findChildren<QRadioButton *>(); // Get all radio buttons in the groupBox
        for (auto radioButton : radioButtons) {
            if (radioButton->isChecked()) { // Check if the radio button is checked
                game_mode_name = radioButton->text();
                break;
            }
        }

        int game_mode = 0;
        if (game_mode_name == "Survival")
            game_mode = 1;
        if (game_mode_name == "Clear the Zone")
            game_mode = 2;
        
        emit matchInfoEntered(ui->match_name_input->toPlainText(), ui->player_name_input->toPlainText(), game_mode, this->commands, this->create_or_join_command);
        choose_soldier->setModal(true);
        choose_soldier->exec();
    }
}
