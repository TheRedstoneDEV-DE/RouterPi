#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main(){
    string lang = "EN";
    string dnsServerAdress;
    string startOnBoot;
    string dhcpConf;
    string ethInterface;
    string wlanInterface;
    string ip;
    string netmask;


    cout << "|–––\\    –––––––––   |       |  ––––––––––––––  |––––––   |–––\\           |––––\\     –––  \n";
    cout << "|    |   |       |   |       |       | |        |         |   |           |     |     |\n";
    cout << "|    /   |       |   |       |       | |        |         |   /           |     /     |\n";
    cout << "|–––     |       |   |       |       | |        |–––      |–––     ––––   |––––       |\n";
    cout << "|–|      |       |   |       |       | |        |         |–|             |           |\n";
    cout << "|  –|    |       |   |–     –|       | |        |         | –|            |           |\n";
    cout << "|   –|   –––––––––    |–––––|        | |        |––––––   |  –|           |          –––  \n";

    cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\nBy TheRedstoneDEV_DE\n";
    cout << "Please select your language of the installer by typing in 'EN' for English or 'DE' for German: ";
    cin >> lang;
    cout << "You have chosen:" << lang << "\n";
    if(lang == "DE"){
        cout << "Schitt 1: Installieren von benötigten Paken über APT\n";
        cout << "Installiere dnsmasq...\n";
        system("sudo apt install dnsmasq");
        cout << "\nInstalliere iptables...\n";
        system("sudo apt install iptables");
        cout << "\nSchritt 1 abgeschlossen!";
        cout << "\nSchritt 2: Konf9igurieren der Pakete";
        cout << "\nWelcher DNS-Server soll bei Anfragen verwendet werden [Standart 8.8.8.8]? ";
        cin >> dnsServerAdress;
        cin.ignore( '\n' );
        cout << "\nSoll die Netzwerkbrücke zwischen wlanX und ethX automatisch beim Booten gestartet werden?[Y/N](pi only!)";
        cin >> startOnBoot;
        cin.ignore( '\n' );
        cout << "\nGebe den Bereich des DHCP servers, welcher auf ethX laufen soll an[Standart: 192.168.2.2,192.168.2.100,12h][Format: <Startadresse>,<Endadresse>,<Leasingzeit>]: ";
        cin >> dhcpConf;
        cin.ignore( '\n' );
        cout << "\nName des Ethernet interfaces, welches verwendet werden soll [Standart eth0]: ";
        cin >> ethInterface;
        cin.ignore( '\n' );
        cout << "\nName des WLan interfaces, welches verwendet werden soll [Standart wlan0]: ";
        cin >> wlanInterface;
        cin.ignore( '\n' );
        cout << "\nWelche IP soll dieses Gerät im Lan haben? [Standart 192.168.2.1]: ";
        cin >> ip;
        cin.ignore( '\n' );
        cout << "\nWelche Netzwektmaske wird im Lan verwendet? [Standart 255.255.255.0]: ";
        cin >> netmask;
        cin.ignore( '\n' );
        cout << "\nEinstellungen werden in die Dateien geschrieben...\n";
        ofstream stream1("/etc/dnsmasq.d/custom-dnsmasq.conf");
        stream1 << "interface=" << ethInterface << "\nbind-interfaces\nserver=" << dnsServerAdress << "\ndomain-needed\nbogus-priv\ndhcp-range=" << dhcpConf;
        stream1.close();
        ofstream stream2("startBridge.sh");
        stream2 << "#!/bin/bash\nsudo systemctl start network-online.target &> /dev/null\nsudo iptables -F\nsudo iptables -t nat -F\nsudo iptables -t nat -A POSTROUTING -o "<< wlanInterface <<" -j MASQUERADE\nsudo iptables -A FORWARD -i " << wlanInterface << " -o " << ethInterface << " -m state --state RELATED,ESTABLISHED -j ACCEPT\nsudo iptables -A FORWARD -i " << ethInterface << " -o " << wlanInterface << " -j ACCEPT\nsudo ifconfig " << ethInterface << " down\nsudo ifconfig " << ethInterface << " up\nsudo ifconfig " << ethInterface << " " << ip << " netmask " << netmask << "\nsudo ip route del 0/0 dev " << ethInterface << " &> /dev/null";
        stream2.close();
        cout << "\nFertig! Starte jetzt den Computer neu!\nFühre nach dem Neustart die startBridge.sh aus und du bist ferig! Die Ports sind gebrückt!\n";
        if(startOnBoot == "Y"){
          ofstream outfile;

          outfile.open("rc.local", std::ios_base::app); // append instead of overwrite
          outfile << "bash /home/pi/startBridge.sh";
        }
    }else{
        cin.ignore( numeric_limits <streamsize> ::max(), '\n' );
        cout << "Step 1: Installation of required software-packages via APT\n";
        cout << "Installing dnsmasq...\n";
        system("sudo apt install dnsmasq");
        cout << "\nInstallig iptables...";
        system("sudo apt install iptables");
        cout << "\nFinished step 1!";
        cout << "\nStep 2: Cofigurering the packages";
        cout << "\nWhich DNS server should be used by default? [Default 8.8.8.8]? ";
        cin >> dnsServerAdress;
        cin.ignore( '\n' );
        cout << "\nShould the bridge be started at Boot-progress? [Y/N](pi only!)";
        cin >> startOnBoot;
        cin.ignore( '\n' );
        cout << "\nType in the dhcp range for the DHCP server running on ethX [Default: 192.168.2.2,192.168.2.100,12h][Format: <Startadress>,<Endadress>,<Leasingtime>]: ";
        cin >> dhcpConf;
        cin.ignore( '\n' );
        cout << "\nWhich interface schould be used as ethernet interface? [Default: eth0]: ";
        cin >> ethInterface;
        cin.ignore( '\n' );
        cout << "\nWhich interface should be used as wifi interface? [Default: wlan0]: ";
        cin >> wlanInterface;
        cin.ignore( '\n' );
        cout << "\nWhich IP should have the computer in the ethernet network? [Default: 192.168.2.1]: ";
        cin >> ip;
        cin.ignore( '\n' );
        cout << "\nWhich netmask has the ethernet? [Standart 255.255.255.0]: ";
        cin >> netmask;
        cin.ignore( '\n' );
        cout << "\nWriting settings to file...\n";
        ofstream stream1("/etc/dnsmasq.d/custom-dnsmasq.conf");
        stream1 << "interface=" << ethInterface << "\nbind-interfaces\nserver=" << dnsServerAdress << "\ndomain-needed\nbogus-priv\ndhcp-range=" << dhcpConf;
        stream1.close();
        ofstream stream2("startBridge.sh");
        stream2 << "#!/bin/bash\nsudo systemctl start network-online.target &> /dev/null\nsudo iptables -F\nsudo iptables -t nat -F\nsudo iptables -t nat -A POSTROUTING -o "<< wlanInterface <<" -j MASQUERADE\nsudo iptables -A FORWARD -i " << wlanInterface << " -o " << ethInterface << " -m state --state RELATED,ESTABLISHED -j ACCEPT\nsudo iptables -A FORWARD -i " << ethInterface << " -o " << wlanInterface << " -j ACCEPT\nsudo ifconfig " << ethInterface << " down\nsudo ifconfig " << ethInterface << " up\nsudo ifconfig " << ethInterface << " " << ip << " netmask " << netmask << "\nsudo ip route del 0/0 dev " << ethInterface << " &> /dev/null";
        stream2.close();
        cout << "\nFinished! Now just reboot the computer and start the script named \nstartBridge.sh and you're done! The ethX and wlanX interfaces are bridged!\n";
        if(startOnBoot == "Y"){
          ofstream outfile;

          outfile.open("rc.local", std::ios_base::app); // append instead of overwrite
          outfile << "bash /home/pi/startBridge.sh";
        }
    }
    return 0;
}
