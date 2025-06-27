/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** main.c
*/

#include "../../include/gui/Command.hpp"
#include "../../include/gui/Error.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "../../include/gui/Graphical.hpp"

std::vector<std::vector<Graphical::Tile>> parse_bct(int *bct, int *msz, std::vector<std::vector<Graphical::Tile>> map)
{
    if (bct[0] < msz[1] && bct[1] < msz[0]) {
        map[bct[0]][bct[1]].food = bct[2];
        map[bct[0]][bct[1]].linemate = bct[3];
        map[bct[0]][bct[1]].deraumere = bct[4];
        map[bct[0]][bct[1]].sibur = bct[5];
        map[bct[0]][bct[1]].mendiane = bct[6];
        map[bct[0]][bct[1]].phiras = bct[7];
        map[bct[0]][bct[1]].thystame = bct[8];
    } else {
        std::cerr << "Indice hors limites : bct[0]=" << bct[0] << ", bct[1]=" << bct[1] << std::endl;
    }
    return map;
}

void drawMap(Graphical &graphical, int *msz, Command &command)
{
    printf("msz: %d %d\n", msz[0], msz[1]);
    // Vérification des dimensions pour éviter le crash du vecteur
    if (msz[0] <= 0 || msz[1] <= 0 || msz[0] > 10000 || msz[1] > 10000) {
        std::cerr << "Invalid map dimensions: " << msz[0] << "x" << msz[1] << std::endl;
        return;
    }
    
    std::vector<std::vector<Graphical::Tile>> map(msz[1], std::vector<Graphical::Tile>(msz[0]));
    for (int i = 0; i < msz[1]; i++) {
        for (int j = 0; j < msz[0]; j++) {
            map[i][j].x = j;
            map[i][j].y = i;
        }
    }
    std::string buffer = graphical.getBuffer();
    size_t pos = 0;
    while ((pos = buffer.find("bct", pos)) != std::string::npos) {
        size_t end = buffer.find('\n', pos);
        std::string bct_line;
        if (end != std::string::npos)
            bct_line = buffer.substr(pos, end - pos);
        else
            bct_line = buffer.substr(pos);
        int *bct = command.handle_bct(bct_line);
        map = parse_bct(bct, msz, map);
        for (int i = 0; i < msz[1]; i++) {
            for (int j = 0; j < msz[0]; j++) {
                graphical.drawTile(map[i][j]);
            }
        }
        pos = (end != std::string::npos) ? end + 1 : buffer.length();
    }
}

std::string extractCommandLine(const std::string &buffer, const std::string &command)
{
    size_t pos = buffer.find(command);
    size_t end = buffer.find('\n', pos);
    std::string command_line;
    
    if (pos != std::string::npos) {
        if (end != std::string::npos)
            command_line = buffer.substr(pos, end - pos);
        else
            command_line = buffer.substr(pos);
    }
    printf("command_line: %s\n", command_line.c_str());
    if (command_line.empty())
        return command_line;
    return command_line;
}

void process_pnw(Graphical &graphical, Command &command)
{
    size_t pos_pnw = 0;
    while ((pos_pnw = graphical.getBuffer().find("pnw", pos_pnw)) != std::string::npos) {
        size_t end_pnw = graphical.getBuffer().find('\n', pos_pnw);
        std::string pnw_line = graphical.getBuffer().substr(pos_pnw, end_pnw - pos_pnw);
        Player currentPlayer = command.handle_pnw(pnw_line);
        graphical.addPlayer(currentPlayer);
        pos_pnw = (end_pnw != std::string::npos) ? end_pnw + 1 : graphical.getBuffer().length();
    }
}

void process_ppo(Graphical &graphical, Command &command)
{
    size_t pos = 0;
    while ((pos = graphical.getBuffer().find("ppo", pos)) != std::string::npos) {
        size_t end = graphical.getBuffer().find('\n', pos);
        std::string ppo_line = graphical.getBuffer().substr(pos, end - pos);
        Player currentPlayer = command.handle_ppo(ppo_line);
        graphical.updatePlayer(currentPlayer);
        pos = (end != std::string::npos) ? end + 1 : graphical.getBuffer().length();
    }
}

void process_tna(Graphical &graphical, Command &command)
{
    size_t pos_tna = 0;

    while ((pos_tna = graphical.getBuffer().find("tna", pos_tna)) != std::string::npos) {
        size_t end_tna = graphical.getBuffer().find('\n', pos_tna);
        std::string tna_line = graphical.getBuffer().substr(pos_tna, end_tna - pos_tna);
        std::string team_name = command.handle_tna(tna_line);
        Graphical::Team team{team_name, sf::Color::White};
        graphical.addTeam(team);
        pos_tna = (end_tna != std::string::npos) ? end_tna + 1 : graphical.getBuffer().length();
    }
    graphical.drawListTeam(graphical.getTeams());
}

void process_plv(Graphical &graphical, Command &command)
{
    size_t pos_plv = 0;
    while ((pos_plv = graphical.getBuffer().find("plv", pos_plv)) != std::string::npos) {
        size_t end_plv = graphical.getBuffer().find('\n', pos_plv);
        std::string plv_line = graphical.getBuffer().substr(pos_plv, end_plv - pos_plv);
        Player currentPlayer = command.handle_plv(plv_line);
        graphical.updateLevel(currentPlayer);
        pos_plv = (end_plv != std::string::npos) ? end_plv + 1 : graphical.getBuffer().length();
    }
}

void process_pin(Graphical &graphical, Command &command)
{
    size_t pos_pin = 0;
    while ((pos_pin = graphical.getBuffer().find("pin", pos_pin)) != std::string::npos) {
        size_t end_pin = graphical.getBuffer().find('\n', pos_pin);
        std::string pin_line = graphical.getBuffer().substr(pos_pin, end_pin - pos_pin);
        Player::Inventory currentInventory = command.handle_pin(pin_line);
        graphical.updateInventory(currentInventory, currentInventory.id);
        pos_pin = (end_pin != std::string::npos) ? end_pin + 1 : graphical.getBuffer().length();
    }
}

void process_pic(Graphical &graphical, Command &command)
{
    size_t pos_pic = 0;
    while ((pos_pic = graphical.getBuffer().find("pic", pos_pic)) != std::string::npos) {
        size_t end_pic = graphical.getBuffer().find('\n', pos_pic);
        std::string pic_line = graphical.getBuffer().substr(pos_pic, end_pic - pos_pic);
        Graphical::Incantation incantation = command.handle_pic(pic_line);
        graphical.setIncantation(incantation);
        pos_pic = (end_pic != std::string::npos) ? end_pic + 1 : graphical.getBuffer().length();
    }
}

void process_pie(Graphical &graphical, Command &command)
{
    size_t pos_pie = 0;
    while ((pos_pie = graphical.getBuffer().find("pie", pos_pie)) != std::string::npos) {
        size_t end_pie = graphical.getBuffer().find('\n', pos_pie);
        std::string pie_line = graphical.getBuffer().substr(pos_pie, end_pie - pos_pie);
        Graphical::Incantation incantation = command.handle_pie(pie_line);
        graphical.setIncantation(incantation);
        pos_pie = (end_pie != std::string::npos) ? end_pie + 1 : graphical.getBuffer().length();
    }
}

void process_pfk(Graphical &graphical, Command &command)
{
    size_t pos_pfk = 0;
    while ((pos_pfk = graphical.getBuffer().find("pfk", pos_pfk)) != std::string::npos) {
        size_t end_pfk = graphical.getBuffer().find('\n', pos_pfk);
        std::string pfk_line = graphical.getBuffer().substr(pos_pfk, end_pfk - pos_pfk);
        int player_id = command.handle_pfk(pfk_line);
        graphical.layingEgg(player_id);
        pos_pfk = (end_pfk != std::string::npos) ? end_pfk + 1 : graphical.getBuffer().length();
    }
} 

void process_enw(Graphical &graphical, Command &command)
{
    size_t pos_enw = 0;
    while ((pos_enw = graphical.getBuffer().find("enw", pos_enw)) != std::string::npos) {
        size_t end_enw = graphical.getBuffer().find('\n', pos_enw);
        std::string enw_line = graphical.getBuffer().substr(pos_enw, end_enw - pos_enw);
        Player::Egg egg = command.handle_enw(enw_line);
        graphical.addEgg(egg);
        pos_enw = (end_enw != std::string::npos) ? end_enw + 1 : graphical.getBuffer().length();
    }
}

void process_ebo(Graphical &graphical, Command &command)
{
    size_t pos_ebo = 0;
    while ((pos_ebo = graphical.getBuffer().find("ebo", pos_ebo)) != std::string::npos) {
        size_t end_ebo = graphical.getBuffer().find('\n', pos_ebo);
        std::string ebo_line = graphical.getBuffer().substr(pos_ebo, end_ebo - pos_ebo);
        Player::Egg egg = command.handle_ebo(ebo_line);
        graphical.hatchEgg(egg.id);
        pos_ebo = (end_ebo != std::string::npos) ? end_ebo + 1 : graphical.getBuffer().length();
    }
}

void process_pdi(Graphical &graphical, Command &command)
{
    size_t pos_pdi = 0;
    while ((pos_pdi = graphical.getBuffer().find("pdi", pos_pdi)) != std::string::npos) {
        size_t end_pdi = graphical.getBuffer().find('\n', pos_pdi);
        std::string pdi_line = graphical.getBuffer().substr(pos_pdi, end_pdi - pos_pdi);
        int player_id = command.handle_pdi(pdi_line);
        graphical.destroyPlayer(player_id);
        pos_pdi = (end_pdi != std::string::npos) ? end_pdi + 1 : graphical.getBuffer().length();
    }
}

void process_edi(Graphical &graphical, Command &command)
{
    size_t pos_edi = 0;
    while ((pos_edi = graphical.getBuffer().find("edi", pos_edi)) != std::string::npos) {
        size_t end_edi = graphical.getBuffer().find('\n', pos_edi);
        std::string edi_line = graphical.getBuffer().substr(pos_edi, end_edi - pos_edi);
        int egg_id = command.handle_edi(edi_line);
        graphical.destroyEgg(egg_id);   
        pos_edi = (end_edi != std::string::npos) ? end_edi + 1 : graphical.getBuffer().length();
    }
}

void process_smg(Graphical &graphical, Command &command)
{
    size_t pos_smg = 0;
    while ((pos_smg = graphical.getBuffer().find("smg", pos_smg)) != std::string::npos) {
        size_t end_smg = graphical.getBuffer().find('\n', pos_smg);
        std::string smg_line = graphical.getBuffer().substr(pos_smg, end_smg - pos_smg);
        std::string message = command.handle_smg(smg_line);
        std::cout << "Message serveur: " << message << std::endl;
        pos_smg = (end_smg != std::string::npos) ? end_smg + 1 : graphical.getBuffer().length();
    }   
}

void process_sgt(Graphical &graphical, Command &command)
{
    size_t pos_sgt = 0;
    while ((pos_sgt = graphical.getBuffer().find("sgt", pos_sgt)) != std::string::npos) {
        size_t end_sgt = graphical.getBuffer().find('\n', pos_sgt);
        std::string sgt_line = graphical.getBuffer().substr(pos_sgt, end_sgt - pos_sgt);
        int freq = command.handle_sgt(sgt_line);
        std::cout << "Fréquence serveur: " << freq << std::endl;
        pos_sgt = (end_sgt != std::string::npos) ? end_sgt + 1 : graphical.getBuffer().length();
    }
}

void process_sst(Graphical &graphical, Command &command)
{
    size_t pos_sst = 0;
    while ((pos_sst = graphical.getBuffer().find("sst", pos_sst)) != std::string::npos) {
        size_t end_sst = graphical.getBuffer().find('\n', pos_sst);
        std::string sst_line = graphical.getBuffer().substr(pos_sst, end_sst - pos_sst);
        int freq = command.handle_sst(sst_line);
        std::cout << "Fréquence modifiée: " << freq << std::endl;
        pos_sst = (end_sst != std::string::npos) ? end_sst + 1 : graphical.getBuffer().length();
    }
}

bool process_seg(Graphical &graphical, Command &command)
{
    size_t pos_seg = 0;
    float time = graphical.getClock().getElapsedTime().asSeconds();
    while ((pos_seg = graphical.getBuffer().find("seg", pos_seg)) != std::string::npos) {
        size_t end_seg = graphical.getBuffer().find('\n', pos_seg);
        std::string seg_line = graphical.getBuffer().substr(pos_seg, end_seg - pos_seg);
        std::string teamName = command.handle_seg(seg_line);
        graphical.gameOver(teamName);
        pos_seg = (end_seg != std::string::npos) ? end_seg + 1 : graphical.getBuffer().length();
        if (time - graphical.getTime() > 1) {
            return true;
        }
    }
    return false;
}

void process_suc(Graphical &graphical, Command &command)
{
    size_t pos_suc = 0;
    while ((pos_suc = graphical.getBuffer().find("suc", pos_suc)) != std::string::npos) {
        size_t end_suc = graphical.getBuffer().find('\n', pos_suc);
        std::string suc_line = graphical.getBuffer().substr(pos_suc, end_suc - pos_suc);
        std::string message = command.handle_suc();
        std::cout << "Message serveur: " << message << std::endl;
        pos_suc = (end_suc != std::string::npos) ? end_suc + 1 : graphical.getBuffer().length();
    }   
}

int processPlayers(Graphical &graphical, Command &command)
{
    //graphical.send_command("Envoyé avec sucess!\n");
    process_tna(graphical, command);
    process_pnw(graphical, command);
    process_ppo(graphical, command);
    process_plv(graphical, command);
    process_pin(graphical, command);
    process_pic(graphical, command);
    process_pie(graphical, command);
    graphical.drawIncantation(graphical.getIncantation());
    process_enw(graphical, command);
    graphical.drawPlayers(command);
    process_pfk(graphical, command);
    process_ebo(graphical, command);
    process_pdi(graphical, command);
    process_edi(graphical, command);    
    process_smg(graphical, command);
    process_sgt(graphical, command);
    process_sst(graphical, command);
    if (process_seg(graphical, command)) {
        return 1;
    }
    process_suc(graphical, command);
    return 0;
}

void processFrame(Graphical &graphical)
{
    graphical.setBuffer(graphical.connectServer(graphical.getHost(), graphical.getPort()));
    Command command(graphical.getBuffer());
    int i = graphical.getInput();
    graphical.clearScreen();

    // Mise à jour de la caméra
    graphical.updateCamera();
    std::string msz_line = extractCommandLine(graphical.getBuffer(), "msz");
    int *msz = command.handle_msz(msz_line);

    // Centrage de la caméra une seule fois
    static bool cameraCentered = false;
    if (!cameraCentered) {
        float centerX = (msz[0] * 66) / 2.0f;
        float centerY = (msz[1] * 66) / 2.0f;
        graphical.getCamera().setPosition(sf::Vector2f(centerX, centerY));
        cameraCentered = true;
    }

    drawMap(graphical, msz, command);
    if (processPlayers(graphical, command) == 1) {
        return;
    }

    graphical.refreshScreen();
}


void runMainLoop(Graphical &graphical)
{
    graphical.init();
    while (graphical.isOpen())
        processFrame(graphical);
}

int main(int ac, char **av)
{
    try {
        int port;
        std::string host;
        if (ac == 2 && std::string(av[1]) == "--help") {
            std::cout << "Usage: ./zappy_gui -p port -h machine" << std::endl;
            return 0;
        } else if (ac == 5 && std::string(av[1]) == "-p" && std::string(av[3]) == "-h") {
            port = std::atoi(av[2]);
            host = av[4];
            std::string machine = av[4];
        } else if (ac == 3 && std::string(av[1]) == "-p") {
            port = std::atoi(av[2]);
            host = "localhost";
        } else
            throw Error("Usage: ./zappy_gui -p <port> -h <machine>");
            
            Graphical graphical(port, host);
            runMainLoop(graphical);
        return 0;
    }
    catch (const Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
