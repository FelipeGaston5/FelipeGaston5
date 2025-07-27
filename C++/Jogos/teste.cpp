#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Weapon
{
public:
    string name;
    int attackBonus;

    Weapon(string n, int a) : name(n), attackBonus(a) {}
};

class Character
{
public:
    string name;
    int health;
    int maxHealth;
    int baseAttack;
    int defense;
    int experience;
    int level;
    Weapon weapon;

    Character(string n, int h, int a, int d, Weapon w)
        : name(n), health(h), maxHealth(h), baseAttack(a), defense(d), experience(0), level(1), weapon(w) {}

    bool isAlive()
    {
        return health > 0;
    }

    int getAttackPower()
    {
        return baseAttack + weapon.attackBonus;
    }

    void takeDamage(int damage)
    {
        int damageTaken = damage - defense;
        if (damageTaken < 0)
            damageTaken = 0;
        health -= damageTaken;
        if (health < 0)
            health = 0;
        cout << name << " recebeu " << damageTaken << " de dano. Vida restante: " << health << "/" << maxHealth << endl;
    }

    void gainExperience(int exp)
    {
        experience += exp;
        cout << name << " ganhou " << exp << " de experiência!" << endl;
        while (experience >= level * 50)
        {
            experience -= level * 50;
            levelUp();
        }
    }

    void levelUp()
    {
        level++;
        maxHealth += 10;
        health = maxHealth;
        baseAttack += 3;
        defense += 2;
        cout << ">>> " << name << " subiu para o nível " << level << "! <<<" << endl;
        cout << "Vida, ataque e defesa aumentaram!" << endl;
    }

    void attackTarget(Character &target)
    {
        int damage = rand() % getAttackPower() + 1;
        cout << name << " ataca " << target.name << " com " << weapon.name << " causando " << damage << " de dano bruto." << endl;
        target.takeDamage(damage);
    }

    void heal(int amount)
    {
        health += amount;
        if (health > maxHealth)
            health = maxHealth;
        cout << name << " se curou " << amount << " pontos. Vida atual: " << health << "/" << maxHealth << endl;
    }
};

void printStatus(const Character &player, const Character &enemy)
{
    cout << "\n===== STATUS =====" << endl;
    cout << player.name << " (Nível " << player.level << ") - Vida: " << player.health << "/" << player.maxHealth << " - EXP: " << player.experience << endl;
    cout << enemy.name << " - Vida: " << enemy.health << "/" << enemy.maxHealth << endl;
    cout << "==================\n"
        << endl;
}

void showMenu()
{
    cout << "Escolha uma ação:" << endl;
    cout << "1 - Atacar" << endl;
    cout << "2 - Defender (reduz dano no próximo ataque)" << endl;
    cout << "3 - Usar poção de cura" << endl;
    cout << "0 - Sair do jogo" << endl;
    cout << ">> ";
}

int main()
{
    srand((unsigned)time(0));

    Weapon sword("Espada de Ferro", 5);
    Weapon claw("Garras", 3);

    Character player("Heroi", 100, 15, 5, sword);
    Character enemy("Goblin", 80, 10, 3, claw);

    int potions = 3;
    bool defending = false;

    cout << "=== BEM-VINDO AO RPG DE TERMINAL ===" << endl;

    while (player.isAlive() && enemy.isAlive())
    {
        printStatus(player, enemy);
        showMenu();

        int choice;
        cin >> choice;

        if (choice == 0)
        {
            cout << "Você saiu do jogo. Até a próxima!" << endl;
            break;
        }

        switch (choice)
        {
        case 1:
        {
            player.attackTarget(enemy);
            defending = false;
            break;
        }
        case 2:
        {
            cout << player.name << " está se defendendo no próximo ataque." << endl;
            defending = true;
            break;
        }
        case 3:
        {
            if (potions > 0)
            {
                cout << player.name << " usou uma poção de cura." << endl;
                player.heal(30);
                potions--;
                defending = false;
            }
            else
            {
                cout << "Você não tem poções sobrando!" << endl;
            }
            break;
        }
        default:
        {
            cout << "Opção inválida!" << endl;
            continue;
        }
        }

        if (!enemy.isAlive())
        {
            cout << enemy.name << " foi derrotado!" << endl;
            player.gainExperience(60);
            break;
        }

        // Vez do inimigo atacar
        cout << enemy.name << " contra-ataca!" << endl;

        int enemyDamage = rand() % enemy.getAttackPower() + 1;
        if (defending)
        {
            enemyDamage /= 2;
            cout << player.name << " defendeu e reduziu o dano pela metade!" << endl;
        }
        player.takeDamage(enemyDamage);

        if (!player.isAlive())
        {
            cout << player.name << " foi derrotado! Fim de jogo." << endl;
            break;
        }
    }

    cout << "=== FIM DO JOGO ===" << endl;
    return 0;
}
