//
//  stream.cpp
//  Search_text
//
//  Created by 袁瑞翔 on 2024/1/5.
//

#include "stream.hpp"
#include "character_info.hpp"
#include "skill.hpp"
#include <limits>
#include<cstring>
#include<iostream>

// 为友军初始化对象
std::vector<FriendCharacter> friends_init(int m){
    // 创建友方对象的容器
    std::vector<FriendCharacter> characters;
    for (int i = 0; i < m; i++)
    {
        int id, character_level, basic_level, BPSkill_level, ultra_level, talent_level, rank;
        std::cout << "请输入第 " << i + 1 << " 个我方角色的信息（ID，角色等级，普攻等级，战技等级，大招等级，天赋等级，星魂等级）" << std::endl;
        int val=-1,cnt=0;
        while(1){
            cnt++;
            std::cin>>val;
            if(std::cin.rdstate()!=0){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize >::max(), '\n');
                std::cin.sync();
                cnt=0;
                break;
            }
            char c=std::cin.get();
            if(c=='\n'){
                //std::cout<<"endline"<<std::endl;
                break;
            }
            else if(c!=' '&&(c<'0'||c>'9')){
                //std::cout<<"err"<<std::endl;
                cnt=0;
                break;
            }
            switch(cnt){
                case 1:
                    id=val;
                    break;
                case 2:
                    character_level = val;
                    break;
                case 3:
                    basic_level = val;
                    break;
                case 4:
                    BPSkill_level = val;
                    break;
                case 5:
                    ultra_level = val;
                    break;
                case 6:
                    talent_level = val;
                    break;
                case 7:
                    rank = val;
                    break;
            }
        }
        if(cnt!=7){
            std::cerr << "输入的数据无效，请重新输入。ERROR:0x01" << std::endl;
            std::cin.sync();
            i--;
            continue;
        }
        // 初始化我方角色 Friendcharacter
        // 检查输入的合法性(包括ID，角色等级，普攻等级，战技、终结、天赋等级，星魂等级）
        if (!isFriendInDictionary(id, characters)|| !isValidCharacterValue(character_level) || !isValidBasicValue(basic_level) || !isValidLevel(BPSkill_level) || !isValidLevel(ultra_level) || !isValidLevel(talent_level) || !isValidRank(rank)) {
            std::cerr << "对象构造失败，请检查输入信息是否合法（超出范围），并重新输入。ERROR:0x02" << std::endl;
            i--;                      // 对象构造失败，重新处理当前对象的输入
        } else {
            FriendCharacter character(id, character_level, basic_level, BPSkill_level, ultra_level, talent_level, rank);
            characters.push_back(character);
            std::cout << "我方角色创建成功。" << std::endl;     // 对象构造成功
        }
    }
    return characters;
}

// 为敌军初始化对象
std::vector<EnemyCharacter> enemies_init(int n){
    // 创建敌方对象的容器
    std::vector<EnemyCharacter> characters;
    for (int i = 0; i < n; i++)
    {
        int id, character_level, basic_level, BPSkill_level, ultra_level, talent_level, rank;
        std::cout << "请输入第 " << i + 1 << " 个敌方角色的信息（ID，角色等级，普攻等级，战技等级，大招等级，天赋等级，星魂等级）" << std::endl;
        int val=-1,cnt=0;
        while(1){
            cnt++;
            std::cin>>val;
            if(std::cin.rdstate()!=0){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize >::max(), '\n');
                std::cin.sync();
                cnt=0;
                break;
            }
            char c=std::cin.get();
            if(c=='\n'){
                //std::cout<<"endline"<<std::endl;
                break;
            }   else if(c!=' '&&(c<'0'||c>'9')){
                //std::cout<<"err"<<std::endl;
                cnt=0;
                break;
            }
        switch(cnt){
                case 1:
                    id=val;
                    break;
                case 2:
                    character_level = val;
                    break;
                case 3:
                    basic_level = val;
                    break;
                case 4:
                    BPSkill_level = val;
                    break;
                case 5:
                    ultra_level = val;
                    break;
                case 6:
                    talent_level = val;
                    break;
                case 7:
                    rank = val;
                    break;
            }
        }
         if(cnt!=7){
            std::cerr << "输入的数据无效，请重新输入。ERROR:0x01" << std::endl;
            std::cin.sync();
            i--;
            continue;
        }
        // 初始化对方角色 Friendcharacter
        // 检查输入的合法性(包括ID，角色等级，普攻等级，战技、终结、天赋等级，星魂等级）
        if (!isEnemyInDictionary(id, characters)|| !isValidCharacterValue(character_level) || !isValidBasicValue(basic_level) || !isValidLevel(BPSkill_level) || !isValidLevel(ultra_level) || !isValidLevel(talent_level) || !isValidRank(rank)) {
            std::cout << "对象构造失败，请检查输入信息是否合法，并重新输入。ERROR:0x02" << std::endl;
            i--;                      // 对象构造失败，重新处理当前对象的输入
        } else {
            EnemyCharacter character(id, character_level, basic_level, BPSkill_level, ultra_level, talent_level, rank);
            characters.push_back(character);
            std::cout << "敌方角色创建成功。" << std::endl;     // 对象构造成功
        }
    }
    return characters;
}


// 判断初始化数据合法性
bool isFriendInDictionary(int id, std::vector<FriendCharacter> vector) {
    // 检查输入的id是否在字典中存在，并且在同一队列不可出现两个相同角色
    if (attribute_dictionary::myDictionary.find(id) != attribute_dictionary::myDictionary.end()){
        for (int i = 0; i < vector.size(); ++i){
            if (id == vector[i].id_get()){
                return false;
            }
        } return true;
    } else return false;
}
bool isEnemyInDictionary(int id, std::vector<EnemyCharacter> vector) {
    // 检查输入的id是否在字典中存在，并且在同一队列不可出现两个相同角色
    if (attribute_dictionary::myDictionary.find(id) != attribute_dictionary::myDictionary.end()){
        for (int i = 0; i < vector.size(); ++i){
            if (id == vector[i].id_get()){
                return false;
            }
        } return true;
    } else return false;
}
bool isValidCharacterValue(int value) {
    // 判定角色等级是否合法
    return value >= 1 && value <= 80;
}
bool isValidBasicValue(int value) {
    // 判定普通攻击等级是否合法
    return value >= 1 && value <= 6;
}
bool isValidLevel(int value) {
    // 判定战技、终结、天赋等级是否合法
    return value >= 1 && value <= 10;
}
bool isValidRank(int value) {
    // 判定星魂等级是否合法
    return value >= 0 && value <= 6;
}


// 初始化时间
void initTime(std::vector<FriendCharacter>& friends, std::vector<EnemyCharacter>& enemies) {
    for (FriendCharacter& character : friends) {
        // 计算我方角色的时间
        character.new_time(10000 / character.spd_get());
    }
    for (EnemyCharacter& character : enemies) {
        // 计算敌方角色的时间
        character.new_time(10000 / character.spd_get());
    }
}
// 创建行动队列 waitingQueue
std::vector<std::pair<CombatCharacter*, bool>> init_waitingQueue(std::vector<FriendCharacter>& friends, std::vector<EnemyCharacter>& enemies) {
    // 创建waitingQueue并将敌我双方pushback
    std::vector<std::pair<CombatCharacter*, bool>> waitingQueue;
    for (FriendCharacter& character : friends) {
        waitingQueue.push_back(std::make_pair(&character, false));
    }
    for (EnemyCharacter& character : enemies) {
        waitingQueue.push_back(std::make_pair(&character, false));
    }
    // 按时间顺序从小到大排序（如果多角色时间相同，则会按照创建时队列顺序排序）
    waitingQueue = new_waitingQueue(waitingQueue);
    return waitingQueue;
}
// 更新行动队列 waitingQueue
std::vector<std::pair<CombatCharacter*, bool>> new_waitingQueue(std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue) {
    // 分离出额外回合和自然回合的角色类指针
    std::vector<std::pair<CombatCharacter*, bool>> trueElements;
    std::vector<std::pair<CombatCharacter*, bool>> falseElements;
    for (const auto& element : waitingQueue) {
        if (element.second) {
            trueElements.push_back(element);
        } else {
            falseElements.push_back(element);
        }
    }
    // 分别按时间顺序从小到大排序（如果多角色时间相同，则会按照创建时队列顺序排序）
    std::sort(trueElements.begin(), trueElements.end(), [](const std::pair<CombatCharacter*, bool>& a, const std::pair<CombatCharacter*, bool>& b) {
        if (a.first->time_get() != b.first->time_get()) {
            return a.first->time_get() < b.first->time_get();
        } else {
            return &a < &b;     // 通过直接比较地址，实现按照初始顺序排序
        }
    });
    std::sort(falseElements.begin(), falseElements.end(), [](const std::pair<CombatCharacter*, bool>& a, const std::pair<CombatCharacter*, bool>& b) {
        if (a.first->time_get() != b.first->time_get()) {
            return a.first->time_get() < b.first->time_get();
        } else {
            return &a < &b;     // 通过直接比较地址，实现按照初始顺序排序
        }
    });
    // 合并排序后的结果
    std::vector<std::pair<CombatCharacter*, bool>> sortedQueue;
    sortedQueue.insert(sortedQueue.end(), trueElements.begin(), trueElements.end());
    sortedQueue.insert(sortedQueue.end(), falseElements.begin(), falseElements.end());
    return sortedQueue;
}

// 获取 waitingQueue 对应回合的属性（自然回合0，额外回合1）
bool getRoundAttribute(const std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue, CombatCharacter* characterPtr) {
    for (const auto& pair : waitingQueue) {
        if (pair.first == characterPtr) {
            return pair.second;
        }
    }
    return false;  // 如果未找到匹配的指针，则返回默认值（false）
}
// 在行动队列中插入角色额外回合
void insertExtraRound(std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue, CombatCharacter* characterPtr) {
    waitingQueue.insert(waitingQueue.begin(), std::make_pair(characterPtr, true));
}
// 在行动队列中移除角色额外回合
void removeExtraRound(std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue) {
    if (!waitingQueue.empty()) waitingQueue.erase(waitingQueue.begin());
}

// 初始化我方角色的位置信息
std::vector<FriendCharacter*> init_friend_positionArray(std::vector<FriendCharacter>& friends){
    std::vector<FriendCharacter*> friend_positionArray;
    for (FriendCharacter& character : friends) {
        friend_positionArray.push_back(&character);
    }
    return friend_positionArray;
}
// 初始化对方角色的位置信息
std::vector<EnemyCharacter*> init_enemy_positionArray(std::vector<EnemyCharacter>& enemies){
    std::vector<EnemyCharacter*> enemy_positionArray;
    for (EnemyCharacter& character : enemies) {
        enemy_positionArray.push_back(&character);
    }
    return enemy_positionArray;
}

// 根据角色状态与属性计算速度
double calculateSpeed (CombatCharacter* character){
    double speed = character -> spd_get();
    for (int i = 0; i < character -> status.size(); ++i){
        if (character -> status[i].name_get() == "禁锢减速"){
            speed *= character -> status[i].value_get();
        }
        if (character -> status[i].name_get() == "禁锢延缓"){
            speed *= character -> status[i].value_get();
        }
        if (character -> status[i].name_get() == "银狼速度下降"){
            speed *= character -> status[i].value_get();
        }
        if (character -> status[i].name_get() == "瓦尔特战技减速"){
            speed *= character -> status[i].value_get();
        }
        if (character -> status[i].name_get() == "希儿自身速度增加"){
            speed *= character -> status[i].value_get();
        }
    }
    return speed;
}
// 根据角色当前速度计算剩余时间
void changeTime(CombatCharacter* characterPtr){
    double distance = characterPtr -> spd_get() * characterPtr -> time_get();
    double speed = calculateSpeed(characterPtr);
    characterPtr -> new_time(distance / speed);
 }
// 跳过行动条的等待时间（领先者直接行动，其他角色时间同步）
void passTime(std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue) {
    double minTime = waitingQueue[0].first->time_get();
    for (auto& pair : waitingQueue) {
        double currentTime = pair.first->time_get();
        pair.first->new_time(currentTime - minTime);
    }
    waitingQueue[0].first->new_time(10000 / calculateSpeed(waitingQueue[0].first));
}

// 查询角色是否可以使用技能
void check_skill(int from, int turn, std::vector<FriendCharacter*> friend_positionArray, std::vector<EnemyCharacter*> enemy_positionArray, std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue, bool* flag){
    
    int from_position;               // 用于记录from在阵营中的位置
    bool from_team = 0;                  // 用于判断我方阵营还是敌方阵营
    bool isNatureRound;              // 用于判断自然回合还是额外回合
    bool tag;                        // 用于判断from与turn是否相等
    
    // 判断我方阵营还是敌方阵营
    if (from >= 0 && from < friend_positionArray.size()) from_team = 0;
    else if (from >= friend_positionArray.size() && from < friend_positionArray.size() + enemy_positionArray.size()) from_team = 1;
    else {
        std::cerr << "输入的指令中角色信息无效，请您重新输入！";
        return;
    }
    
    //计算from和to在各自阵营的位置
    if (from_team == 0) from_position = from;
    else from_position = from_position = static_cast<int>(from - friend_positionArray.size());  // 显式转化unsigned long -> int
    
    // 判断是在自然回合还是额外回合
    if (from_team == 0) isNatureRound = getRoundAttribute(waitingQueue, friend_positionArray[from_position]) == 0;
    else isNatureRound = getRoundAttribute(waitingQueue, enemy_positionArray[from_position]) == 0;
    
    // 判断from与turn是否相等
    tag = from == turn;
    
    // 检查普攻或技能是否可以释放，并反馈输出信息
    if (isNatureRound){
        if (*flag == 0){
            if (tag == 1){
                std::cout << "角色可以释放普通攻击；";
                if (from_team == 0){
                    if (friend_positionArray[from_position] -> skillpoint != 0){
                        std::cout << "战技可以释放；";
                    } else {
                        std::cout << "战技点不足，无法释放战技；";
                    }
                } else {
                    if (enemy_positionArray[from_position] -> skillpoint != 0){
                        std::cout << "战技可以释放；";
                    } else {
                        std::cout << "战技点不足，无法释放战技；";
                    }
                }
            } else {
                std::cout << "不是当前角色的自然回合，无法释放普通攻击；" << "无法释放战技；";
            }
        } else {
            if (tag == 1){
                std::cout << "角色已执行自然回合行动，不可再次释放普攻或战技；";
            } else {
                std::cout << "不是当前角色的自然回合，无法释放普通攻击；" << "无法释放战技；";
            }
        }
    } else {
        if (tag == 1){
            std::cout << "角色可以释放普通攻击；";
            if (from_team == 0){
                if (friend_positionArray[from_position] -> skillpoint != 0){
                    std::cout << "战技可以释放；";
                } else {
                    std::cout << "战技点不足，无法释放战技；";
                }
            } else {
                if (enemy_positionArray[from_position] -> skillpoint != 0){
                    std::cout << "战技可以释放；";
                } else {
                    std::cout << "战技点不足，无法释放战技；";
                }
            }
        } else {
            std::cout << "不是当前角色的额外回合，无法释放普通攻击；" << "无法释放战技；";
        }
    }
    // 检查终极技是否可以释放，并反馈输出信息
    if (isNatureRound) {
        if (from_team == 0){
            if (friend_positionArray[from_position] -> energy_restore_get() == friend_positionArray[from_position] -> energy_max_get()){
                std::cout << "终结技可以释放。" << std::endl;
            } else {
                std::cout << "能量不足，终结技无法释放。" << std::endl;
            }
        } else {
            if (enemy_positionArray[from_position] -> energy_restore_get() == enemy_positionArray[from_position] -> energy_max_get()){
                std::cout << "终结技可以释放。" << std::endl;
            } else {
                std::cout << "能量不足，终结技无法释放。" << std::endl;
            }
        }
    } else {
        std::cout << "额外回合，终结技不可释放。" << std::endl;
    }
}
 
// 查询角色当前属性信息
void check_attribute(CombatCharacter* characterPtr, std::string keywords, int skillpoint){
    if (keywords == "health") std::cout << "id:" << characterPtr -> id_get() << "\t" << "health:" << characterPtr -> hp_get() << '/' << characterPtr -> hp_max_get() << std::endl;
    else if (keywords == "energy") std::cout << "id:" << characterPtr -> id_get() << "\t" << "energy:" << characterPtr -> energy_restore_get() << '/' << characterPtr ->  energy_max_get() << std::endl;
    else if (keywords == "attack") std::cout << "id:" << characterPtr -> id_get() << "\t" << "attack:"  << characterPtr -> atk_get() << std::endl;
    else if (keywords == "defence") std::cout << "id:" << characterPtr -> id_get() << "\t" << "defence:"  << characterPtr -> def_get() << std::endl;
    else if (keywords == "speed") std::cout << "id:" << characterPtr -> id_get() << "\t" << "speed:"  << calculateSpeed(characterPtr) << std::endl;
    else if (keywords == "shield") std::cout << "id:" << characterPtr -> id_get() << "\t" << "shield:"  << characterPtr -> shield_get() << std::endl;
    else if (keywords == "penetrate") std::cout << "id:" << characterPtr -> id_get() << "\t" << "penetrate:"  << characterPtr -> penetrate_get() << std::endl;
    else if (keywords == "crit_rate") std::cout << "id:" << characterPtr -> id_get() << "\t" << "crit_rate:"  << characterPtr -> crit_rate_get() << std::endl;
    else if (keywords == "crit_DMG") std::cout << "id:" << characterPtr -> id_get() << "\t" << "crit_DMG:"  << characterPtr -> crit_DMG_get() << std::endl;
    else if (keywords == "element") std::cout << "id:" << characterPtr -> id_get() << "\t" << "element:"  << characterPtr -> element_get() << std::endl;
    else if (keywords == "skillpoint") std::cout << "id:" << characterPtr -> id_get() << "\t" << "skillpoint:"  << skillpoint << std::endl;
    else if (keywords == "simple"){
        std::cout << "id:" << characterPtr -> id_get() << "\t" << "[" << characterPtr -> hp_get() << '/' << characterPtr -> hp_max_get() << "]\t" << "(" << characterPtr -> shield_get() << ")\t" << "[" << characterPtr -> energy_restore_get() << '/' << characterPtr ->  energy_max_get() << "]" << std::endl;
    }
    else if (keywords == "all"){
        std::cout << "id:" << characterPtr -> id_get() << "\t\t\t" << "element:" << characterPtr -> element_get() << std::endl;
        std::cout << "health:" << characterPtr -> hp_get() << '/' << characterPtr -> hp_max_get() << "\t";
        std::cout << "shield:" << characterPtr -> shield_get() << "\t";
        std::cout << "attack:" << characterPtr -> atk_get() << "\t";
        std::cout << "skillpoint:" << skillpoint << "\t";
        std::cout << "crit_rate:" << characterPtr -> crit_rate_get() << "\n";
        
        std::cout << "energy:" << characterPtr -> energy_restore_get() << '/' << characterPtr ->  energy_max_get() << "\t";
        std::cout << "speed:" << calculateSpeed(characterPtr) << "\t";
        std::cout << "defence:" << characterPtr -> def_get() << "\t";
        std::cout << "penetrate:" << characterPtr -> penetrate_get() << "\t";
        std::cout << "crit_DMG" << characterPtr -> crit_DMG_get() << "\n";
    }
    else std::cerr << "找不到角色的对应信息或角色输入错误 ERROR：0x04" << std::endl;
}

// 查询当前双方战斗状况
void check_combatInfo(std::vector<FriendCharacter*> friend_positionArray, std::vector<EnemyCharacter*> enemy_positionArray){
    std::cout << "我方角色战斗信息：" << std::endl;
    // 遍历我方位置队列中所有角色信息
    for (std::vector<FriendCharacter*>::iterator it = friend_positionArray.begin(); it != friend_positionArray.end(); ++it){
        FriendCharacter* characterPtr = *it;
        check_attribute(characterPtr, "simple", characterPtr -> skillpoint);
    }
    std::cout << "敌方角色战斗信息：" << std::endl;
    for (std::vector<EnemyCharacter*>::iterator it = enemy_positionArray.begin(); it != enemy_positionArray.end(); ++it){
        EnemyCharacter* characterPtr = *it;
        check_attribute(characterPtr, "simple", characterPtr -> skillpoint);
    }
}

// 查询角色当前状态情况
void check_status(CombatCharacter* characterPtr){
    if (characterPtr->status.empty()) {
        std::cout << "代号" << characterPtr -> code_get() << "角色目前没有特殊状态" << std::endl;
    } else {
        for (const Status& status : characterPtr->status) {
            std::cout << status.name_get() << "\t";
        } std::cout << std::endl;
    }
}

// 查询角色当前是否被冻结
bool check_frozen(CombatCharacter* characterPtr){
    bool isFrozen = false;
    if (characterPtr->status.empty()) {
        return isFrozen;
    } else {
        for (const Status& status : characterPtr->status) {
            if (status.name_get() == "冻结") {
                isFrozen = true;
            }
        }
    }
    return isFrozen;
}

// 信息查询函数 Query
void Query(std::string input, int turn, std::vector<FriendCharacter*> friend_positionArray, std::vector<EnemyCharacter*> enemy_positionArray, std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue, bool* flag){
    // 解析输入
    std::istringstream iss(input);
    std::string command, id, option;
    iss >> command >> id >> option;
    // 将输入的数字格式转化为int，如果非法则报错
    int from;
    bool team = 0;
    // 将string格式转化为int
    try {
        from = std::stoi(id);
    } catch (const std::invalid_argument& e) {
        std::cerr << "输入的指令数据不合法，请您重新输入！" << std::endl;
        return;
    }
    // 判断我方阵营还是敌方阵营
    if (from >= 0 && from < friend_positionArray.size()) team = 0;
    else if (from >= friend_positionArray.size() && from < friend_positionArray.size() + enemy_positionArray.size()) team = 1;
    else {
        std::cerr << "输入的指令中角色信息无效，请您重新输入！";
        return;
    }
    
    // 将 FriendCharacter* 转换为 CombatCharacter*
    std::vector<CombatCharacter*> friendCombatArray(friend_positionArray.begin(), friend_positionArray.end());
    // 将 EnemyCharacter* 转换为 CombatCharacter*
    std::vector<CombatCharacter*> enemyCombatArray(enemy_positionArray.begin(), enemy_positionArray.end());
    
    // 输入合法性检验，并通过id查找到类指针
    CombatCharacter* characterPtr = team == 0 ? friendCombatArray[from] : enemyCombatArray[from - friendCombatArray.size()];
    
    // 根据传入指令调用相应函数
    if (option == "status") {
        check_status(characterPtr);
    } else if (option == "health" || option == "shield" || option == "attack" || option == "defence" || option == "energy" || option == "skillpoint" || option == "speed" || option == "crit_rate" || option == "crit_DMG" || option == "penetrate" || option == "all" || option == "simple"){
        check_attribute(characterPtr, option, team == 0 ? friend_positionArray[from] -> skillpoint : enemy_positionArray[from - friend_positionArray.size()] -> skillpoint);
    } else if (option == "skill"){
        check_skill(from, turn, friend_positionArray, enemy_positionArray, waitingQueue, flag);
    } else {
        std::cerr << "输入的查询指令不合法，请您重新输入" << std::endl;
    }
}

// 回合跳过函数 Skip
bool Skip(std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue, bool flag) {
    if (!waitingQueue.empty() && waitingQueue[0].second == 0) {
        if (flag == 1) {
            std::cout << "当前自然回合结束，进入下一回合" << std::endl;
            // 进入新的回合，更新status状态，更新剩余时间
            for (std::pair<CombatCharacter*, bool>& element : waitingQueue) {
                CombatCharacter* characterPtr = element.first;
                changeTime(characterPtr);
                characterPtr->updateStatus();
            }
            // 进入新的回合，更新行动序列
            waitingQueue = new_waitingQueue(waitingQueue);
            return true;
        } else {
            std::cerr << "角色" << "在自然回合中尚未行动，不可跳过" << std::endl;
            return false;
        }
    } else if (!waitingQueue.empty() && waitingQueue[0].second == 1) {
        std::cerr << "角色" << "在额外回合中尚未行动，不可跳过" << std::endl;
        return false;
    } else {
        std::cerr << "错误！行动队列为空" << std::endl;
        return false;
    }
}

// 行动执行函数 Execute
bool Execute(std::string input, bool team, int turn, std::vector<FriendCharacter*>& friend_positionArray, std::vector<EnemyCharacter*>& enemy_positionArray, std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue, bool* flag){
    // 解析输入
    std::istringstream iss(input);
    std::string command, characterIndex, skill, targetIndex;
    int cnt=0;
    std::string tmpstring;
        while(iss>>tmpstring){
            cnt++;
            //std::cout<<tmpstring<<std::endl;
            if(std::cin.rdstate()!=0){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize >::max(), '\n');
                std::cin.sync();
                cnt=0;
                break;
            }
            //char c=std::cin.get();
            if(cnt>=5){
                //std::cout<<"endline"<<std::endl;
                break;
            }
        switch(cnt){
            case 1:
                command=tmpstring;
                break;
            case 2:
                characterIndex=tmpstring;
                break;
            case 3:
                skill=tmpstring;
                break;
            case 4:
                targetIndex=tmpstring;
                break;
            }
        }
        if(cnt!=4){
            std::cin.sync(); 
            std::cerr << "输入的指令数据不合法(参数过多)，请您重新输入！" << std::endl;    
            return 0;
        }
    // 将输入的数字格式转化为int，如果非法则报错
    int from, to;
    try {
        from = std::stoi(characterIndex);
        to = std::stoi(targetIndex);
    } catch (const std::invalid_argument& e) {
        std::cerr << "输入的指令数据不合法，请您重新输入！" << std::endl;
        return 0;
    }
    
    // 将 FriendCharacter* 转换为 CombatCharacter*
    std::vector<CombatCharacter*> friendCombatArray(friend_positionArray.begin(), friend_positionArray.end());
    // 将 EnemyCharacter* 转换为 CombatCharacter*
    std::vector<CombatCharacter*> enemyCombatArray(enemy_positionArray.begin(), enemy_positionArray.end());
    
    // 初始化检查点信息
    short state = -1;
    short result = 0;
    bool from_team = 0;
    bool to_team = 0;        // 用于判断from和to的阵营
    bool isNatureRound;             // 用于判断是在自然回合还是额外回合
    int from_position, to_position; // 用于计算from和to在各自阵营的位置
        
    // 判断from和to的阵营
    if (from >= 0 && from < friendCombatArray.size()) from_team = 0;
    else if (from >= friendCombatArray.size() && from < friendCombatArray.size() + enemyCombatArray.size()) from_team = 1;
    else {
        std::cerr << "输入的指令中角色信息无效，请您重新输入！";
        return 0;
    }
    if (to >= 0 && to < friendCombatArray.size()) to_team = 0;
    else if (to >= friendCombatArray.size() && to < friendCombatArray.size() + enemyCombatArray.size()) to_team = 1;
    else {
        std::cerr << "输入的指令中角色信息无效，请您重新输入！";
        return 0;
    }
        
    //计算from和to在各自阵营的位置
    if (from_team == 0) from_position = from;
    else from_position = static_cast<int>(from - friendCombatArray.size());  // 显式转化unsigned long -> int
    if (to_team == 0) to_position = to;
    else to_position = static_cast<int>(to - friendCombatArray.size());        // 显式转化unsigned long -> int
    
    // 判断是在自然回合还是额外回合
    if (from_team == 0) isNatureRound = getRoundAttribute(waitingQueue, friend_positionArray[from_position]) == 0;
    else isNatureRound = getRoundAttribute(waitingQueue, enemy_positionArray[from_position]) == 0;
    
    // 集齐七层缩进，召唤技能!
    if (isNatureRound) {
        if (skill == "ultra"){
            if (from_team == 0){
                if (friend_positionArray[from_position] -> energy_restore_get() == friend_positionArray[from_position] -> energy_max_get()){
                    state = *friend_positionArray[from_position]->check_ultra(from_team, to_team);
                    switch (state){
                        case -1:
                            std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                            return 0;
                        case 0:
                            std::cout << "执行代号" << friend_positionArray[from_position]->id_get() << "角色终结技成功\n";
                            result = *friend_positionArray[from_position]->ultra(from_position, to_position, friendCombatArray, enemyCombatArray);
                            break;
                        case -2:
                            std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色终结技应作用于同一阵营角色，请您重新输入：\n";
                            return 0;
                        case -3:
                            std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色终结技应作用于对手阵营角色，请您重新输入：\n";
                            return 0;
                    }
                } else {
                    std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色能量不足，不能使用终结技 ERROR:0x08" << std::endl;
                    return 0;
                }
            } else {
                if (enemy_positionArray[from_position] -> energy_restore_get() == enemy_positionArray[from_position] -> energy_max_get()){
                    state = *enemy_positionArray[from_position]->check_ultra(from_team, to_team);
                    switch (state){
                        case -1:
                            std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                            return 0;
                        case 0:
                            std::cout << "执行代号" << enemy_positionArray[from_position]->id_get() << "角色终结技成功\n";
                            result = *enemy_positionArray[from_position]->ultra(from_position, to_position, enemyCombatArray, friendCombatArray);
                            break;
                        case -2:
                            std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色终结技应作用于同一阵营角色，请您重新输入：\n";
                            return 0;
                        case -3:
                            std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色终结技应作用于对手阵营角色，请您重新输入：\n";
                            return 0;
                    }
                } else {
                    std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色能量不足，不能使用终结技 ERROR:0x08" << std::endl;
                    return 0;
                }
            }
        } else if (skill == "bpskill") {
            if (*flag == 0){
                if (from == turn){
                    if (from_team == 0){
                        if (friend_positionArray[from_position]->skillpoint != 0){
                            state = *friend_positionArray[from_position]->check_skill(from_team, to_team);
                            switch (state){
                                case -1:
                                    std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                                    return 0;
                                case 0:
                                    std::cout << "执行代号" << friend_positionArray[from_position]->id_get() << "角色战技成功\n";
                                    result = *friend_positionArray[from_position]->skill(from_position, to_position, friendCombatArray, enemyCombatArray);
                                    friend_positionArray[from_position]->skillpoint--;
                                    passTime(waitingQueue);
                                    break;
                                case -2:
                                    std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色战技应作用于同一阵营角色，请您重新输入：\n";
                                    return 0;
                                case -3:
                                    std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色战技应作用于对手阵营角色，请您重新输入：\n";
                                    return 0;
                            }
                        } else {
                            std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色战技点不足，不能使用战技 ERROR:0x06" << std::endl;
                            return 0;
                        }
                    } else {
                        if (enemy_positionArray[from_position]->skillpoint != 0){
                            state = *enemy_positionArray[from_position]->check_skill(from_team, to_team);
                            switch (state){
                                case -1:
                                    std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                                    return 0;
                                case 0:
                                    std::cout << "执行代号" << enemy_positionArray[from_position]->id_get() << "角色战技成功\n";
                                    result = *enemy_positionArray[from_position]->skill(from_position, to_position, enemyCombatArray, friendCombatArray);
                                    enemy_positionArray[from_position]->skillpoint--;
                                    passTime(waitingQueue);
                                    break;
                                case -2:
                                    std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色战技应作用于同一阵营角色，请您重新输入：\n";
                                    return 0;
                                case -3:
                                    std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色战技应作用于对手阵营角色，请您重新输入：\n";
                                    return 0;
                            }
                        } else {
                            std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色战技点不足，不能使用战技 ERROR:0x06" << std::endl;
                            return 0;
                        }
                    }
                } else {
                    if (from_team == 0){
                        std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色不属于当前角色回合，不能使用普攻或战技 ERROR:0x07" << std::endl;
                        return 0;
                    } else {
                        std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色不属于当前角色回合，不能使用普攻或战技 ERROR:0x07" << std::endl;
                        return 0;
                    }
                }
            } else {
                if (from == turn) {
                    if (from_team == 0){
                        std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "已经完成自然回合行动，同一回合不能重复行动，请您输入 Skip 进入下一回合" << std::endl;
                        return 0;
                    } else {
                        std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "已经完成自然回合行动，同一回合不能重复行动，请您输入 Skip 进入下一回合" << std::endl;
                        return 0;
                    }
                } else {
                    if (from_team == 0){
                        std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色不属于当前角色回合，不能使用普攻或战技 ERROR:0x07" << std::endl;
                        return 0;
                    } else {
                        std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色不属于当前角色回合，不能使用普攻或战技 ERROR:0x07" << std::endl;
                        return 0;
                    }
                }
            }
        } else if (skill == "normal") {
            if (*flag == 0){
                if (from == turn){
                    if (from_team == 0){
                        state = *friend_positionArray[from_position]->check_normal(from_team, to_team);
                        switch (state){
                            case -1:
                                std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                                return 0;
                            case 0:
                                std::cout << "执行代号" << friend_positionArray[from_position]->id_get() << "角色普攻成功\n";
                                result = *friend_positionArray[from_position]->normal(from_position, to_position, friendCombatArray, enemyCombatArray);
                                friend_positionArray[from_position]->skillpoint++;
                                passTime(waitingQueue);
                                break;
                            case -2:
                                std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色普攻应作用于同一阵营角色，请您重新输入：\n";
                                return 0;
                            case -3:
                                std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色普攻应作用于对手阵营角色，请您重新输入：\n";
                                return 0;
                        }
                    } else {
                        state = *enemy_positionArray[from_position]->check_normal(from_team, to_team);
                        switch (state){
                            case -1:
                                std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                                return 0;
                            case 0:
                                std::cout << "执行代号" << enemy_positionArray[from_position]->id_get() << "角色普攻成功\n";
                                result = *enemy_positionArray[from_position]->normal(from_position, to_position, enemyCombatArray, friendCombatArray);
                                enemy_positionArray[from_position]->skillpoint++;
                                passTime(waitingQueue);
                                break;
                            case -2:
                                std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色普攻应作用于同一阵营角色，请您重新输入：\n";
                                return 0;
                            case -3:
                                std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色普攻应作用于对手阵营角色，请您重新输入：\n";
                                return 0;
                        }
                    }
                } else {
                    if (from_team == 0){
                        std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色不属于当前角色回合，不能使用普攻或战技 ERROR:0x07" << std::endl;
                        return 0;
                    } else {
                        std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色不属于当前角色回合，不能使用普攻或战技 ERROR:0x07" << std::endl;
                        return 0;
                    }
                }
            } else {
                if (from == turn) {
                    if (from_team == 0){
                        std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "已经完成自然回合行动，同一回合不能重复行动，请您输入 Skip 进入下一回合" << std::endl;
                        return 0;
                    } else {
                        std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "已经完成自然回合行动，同一回合不能重复行动，请您输入 Skip 进入下一回合" << std::endl;
                        return 0;
                    }
                } else {
                    if (from_team == 0){
                        std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色不属于当前角色回合，不能使用普攻或战技 ERROR:0x07" << std::endl;
                        return 0;
                    } else {
                        std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色不属于当前角色回合，不能使用普攻或战技 ERROR:0x07" << std::endl;
                        return 0;
                    }
                }
            }
        } else {
            std::cerr << "输入的指令行动不合法，请您重新输入： ERROR:0x09";
            return 0;
        }
    } else {
        if (skill == "bpskill") {
            if (from == turn){
                if (from_team == 0){
                    if (friend_positionArray[from_position]->skillpoint != 0){
                        state = *friend_positionArray[from_position]->check_skill(from_team, to_team);
                        switch (state){
                            case -1:
                                std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                                return 0;
                            case 0:
                                std::cout << "执行代号" << friend_positionArray[from_position]->id_get() << "角色战技成功\n";
                                result = *friend_positionArray[from_position]->skill(from_position, to_position, friendCombatArray, enemyCombatArray);
                                friend_positionArray[from_position]->skillpoint--;
                                break;
                            case -2:
                                std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色战技应作用于同一阵营角色，请您重新输入：\n";
                                return 0;
                            case -3:
                                std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色战技应作用于对手阵营角色，请您重新输入：\n";
                                return 0;
                        }
                    } else {
                        std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色战技点不足，不能使用战技 ERROR:0x06" << std::endl;
                        return 0;
                    }
                } else {
                    if (enemy_positionArray[from_position]->skillpoint != 0){
                        state = *enemy_positionArray[from_position]->check_skill(from_team, to_team);
                        switch (state){
                            case -1:
                                std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                                return 0;
                            case 0:
                                std::cout << "执行代号" << enemy_positionArray[from_position]->id_get() << "角色战技成功\n";
                                result = *enemy_positionArray[from_position]->skill(from_position, to_position, enemyCombatArray, friendCombatArray);
                                enemy_positionArray[from_position]->skillpoint--;
                                break;
                            case -2:
                                std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色战技应作用于同一阵营角色，请您重新输入：\n";
                                return 0;
                            case -3:
                                std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色战技应作用于对手阵营角色，请您重新输入：\n";
                                return 0;
                        }
                    } else {
                        std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色战技点不足，不能使用战技 ERROR:0x06" << std::endl;
                        return 0;
                    }
                }
            } else {
                if (from_team == 0){
                    std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色不属于当前额外回合，无法行动" << std::endl;
                    return 0;
                } else {
                    std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色不属于当前额外回合，无法行动" << std::endl;
                    return 0;
                }
            }
        } else if (skill == "normal"){
            if (from == turn){
                if (from_team == 0){
                    state = *friend_positionArray[from_position]->check_normal(from_team, to_team);
                    switch (state){
                        case -1:
                            std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                            return 0;
                        case 0:
                            std::cout << "执行代号" << friend_positionArray[from_position]->id_get() << "角色普攻成功\n";
                            result = *friend_positionArray[from_position]->normal(from_position, to_position, friendCombatArray, enemyCombatArray);
                            friend_positionArray[from_position]->skillpoint++;
                            break;
                        case -2:
                            std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色普攻应作用于同一阵营角色，请您重新输入：\n";
                            return 0;
                        case -3:
                            std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色普攻应作用于对手阵营角色，请您重新输入：\n";
                            return 0;
                    }
                } else {
                    state = *enemy_positionArray[from_position]->check_normal(from_team, to_team);
                    switch (state){
                        case -1:
                            std::cerr << "输入的指令数据不合法，请您重新输入：" << std::endl;
                            return 0;
                        case 0:
                            std::cout << "执行代号" << enemy_positionArray[from_position]->id_get() << "角色普攻成功\n";
                            result = *enemy_positionArray[from_position]->normal(from_position, to_position, enemyCombatArray, friendCombatArray);
                            enemy_positionArray[from_position]->skillpoint++;
                            break;
                        case -2:
                            std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色普攻应作用于同一阵营角色，请您重新输入：\n";
                            return 0;
                        case -3:
                            std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色普攻应作用于对手阵营角色，请您重新输入：\n";
                            return 0;
                    }
                }
            } else {
                if (from_team == 0){
                    std::cerr << "代号" << friend_positionArray[from_position]->code_get() << "角色不属于当前额外回合，无法行动" << std::endl;
                    return 0;
                } else {
                    std::cerr << "代号" << enemy_positionArray[from_position]->code_get() << "角色不属于当前额外回合，无法行动" << std::endl;
                    return 0;
                }
            }
        } else if (skill == "ultra"){
            std::cerr << "处于额外回合，终结技释放无效" << std::endl;
            return 0;
        } else {
            std::cerr << "输入的指令行动不合法，请您重新输入： ERROR:0x09";
            return 0;
        }
    }
    for(int i = 0;i < (int)friend_positionArray.size();++i){
        if(i>=friendCombatArray.size()||friend_positionArray[i]->id_get()!=friendCombatArray[i]->id_get()){
            friend_positionArray.erase(friend_positionArray.begin()+i);
            i--;
        }
    }
    for(int i = 0;i < (int)enemy_positionArray.size();++i){
        if(i>=enemyCombatArray.size()||enemy_positionArray[i]->id_get()!=enemyCombatArray[i]->id_get()){
            enemy_positionArray.erase(enemy_positionArray.begin()+i);
            i--;
        }
    }
    for(int i = 0;i < waitingQueue.size();++i){
        if(waitingQueue[i].first -> team_get() == 0){
            bool flag = false;
            for (int j = 0;j < (int)friend_positionArray.size();++j){
                if(friend_positionArray[j]->id_get()==waitingQueue[i].first->id_get()){
                    flag = true;
                    break;
                }
            } if (flag == false) waitingQueue.erase(waitingQueue.begin() + i);
        } else {
            bool flag = false;
            for (int j = 0;j < (int)enemy_positionArray.size();++j){
                if(enemy_positionArray[j]->id_get()==waitingQueue[i].first->id_get()){
                    flag = true;
                    break;
                }
            } if (flag == false) waitingQueue.erase(waitingQueue.begin() + i);
        }
    }
    // 当行动正常执行，根据返回值和当前状态更新状态
    //std::cout<<result<<std::endl;
switch (result){
    case 0:
        break;
    case 1:
        *flag = 1;
        break;
    case 2:
        /*
        for (auto& pair : waitingQueue) {
            std::cout << pair.first->time_get() << std::endl;
        }*/
        if (waitingQueue[0].second == 0){
            insertExtraRound(waitingQueue, from_team == 0 ? friendCombatArray[from_position] : enemyCombatArray[from_position]);
        } else removeExtraRound(waitingQueue);
        /*for (auto& pair : waitingQueue) {
            std::cout << pair.first->time_get() << std::endl;
        }*/
        break;
    case 3:
        *flag = 1;
        /*
        for (auto& pair : waitingQueue) {
            std::cout << pair.first->time_get() << std::endl;
        }
        */
        if (waitingQueue[0].second == 0){
            insertExtraRound(waitingQueue, from_team == 0 ? friendCombatArray[from_position] : enemyCombatArray[from_position]);
        } else removeExtraRound(waitingQueue);
        /*for (auto& pair : waitingQueue) {
            std::cout << pair.first->time_get() << std::endl;
        }*/
        
        break;
    }
    return 1;
}
//1102 30 1 1 1 1 1 1
//1102 1 1 1 1 1 1
//execute 0 bpskill 1
bool isGameFinish(std::vector<FriendCharacter*> friend_positionArray, std::vector<EnemyCharacter*> enemy_positionArray){
    if (friend_positionArray.size() == 0 && enemy_positionArray.size() == 0){
        throw std::runtime_error("错误：双方队列均为空");
        return true;
    } else if (friend_positionArray.size() == 0 && enemy_positionArray.size() != 0) {
        std::cout << "敌方获胜，游戏结束" << std::endl;
        return true;
    } else if (friend_positionArray.size() != 0 && enemy_positionArray.size() == 0) {
        std::cout << "我方获胜，游戏结束" << std::endl;
        return true;
    } else return false;
}

bool mainGame(std::vector<FriendCharacter*>& friend_positionArray, std::vector<EnemyCharacter*>& enemy_positionArray, std::vector<std::pair<CombatCharacter*, bool>>& waitingQueue, bool* flag){
    
    // 检测skip执行成功与否
    *flag = 0;
    bool skip_res = 0;
    bool isRoundOver = 0;
    bool isGameOver = 0;
    
    while (!isRoundOver){
        std::cout << "***********************************************************" << std::endl;
        // 找到剩余时间最短的对象id
        CombatCharacter* shortestTimeCharacter = waitingQueue[0].first;
        bool team = shortestTimeCharacter -> team_get();
        
        // 查找waitingQueue中当前角色在positionArray的位置
        int turn = 0;       // 当前角色在positionArray中的位置
        int code = 0;       // 当前角色对应的code序号
        if (team == 0){
            for (; turn < friend_positionArray.size(); ++turn){
                if (shortestTimeCharacter -> id_get() == friend_positionArray[turn] -> id_get()) break;
            } code = friend_positionArray[turn] -> code_get();
        } else {
            for (; turn < enemy_positionArray.size(); ++turn){
                if (shortestTimeCharacter -> id_get() == enemy_positionArray[turn] -> id_get()) break;
            } code = enemy_positionArray[turn] -> code_get();
        }
        
        // 输出进度条
        for (auto& pair : waitingQueue) {
            std::cout << pair.first->time_get() << std::endl;
        }
        
        // 输出当前角色基础信息
        if (team == 0 && waitingQueue[0].second == 0) std::cout << "当前回合是我方 "  << friend_positionArray[turn] -> id_get()  << " 角色的角色回合" << "，该角色的代号为 " << code << "，该角色位置为 " << turn << std::endl;
        else if (team != 0 && waitingQueue[0].second == 0) std::cout << "当前回合是对方 " << enemy_positionArray[turn] -> id_get()  << " 角色的角色回合" << "，该角色的代号为 " << code << "，该角色位置为 " << turn << std::endl;
        else if (team == 0 && waitingQueue[0].second == 1) std::cout << "当前回合是我方 "  << friend_positionArray[turn] -> id_get()  << " 角色的额外回合" << "，该角色的代号为 " << code << "，该角色位置为 " << turn << std::endl;
        else if (team != 0 && waitingQueue[0].second == 1) std::cout << "当前回合是对方 " << enemy_positionArray[turn] -> id_get()  << " 角色的额外回合" << "，该角色的代号为 " << code << "，该角色位置为 " << turn << std::endl;
        
        // 判断当前回合角色的异常状态，如果角色被冻结，则自动跳过此回合
        if (check_frozen(shortestTimeCharacter)) skip_res = Skip(waitingQueue, true);
        
        // 输出当前角色可释放的技能信息
        check_skill(code, code, friend_positionArray, enemy_positionArray, waitingQueue, flag);
        
        // 等待用户输入交互
        std::string input;
        std::cout << "请您输入操作指令: ";
        std::getline(std::cin, input);   // 获取一行输入
        
        std::cout << input << (input.find("execute") == 0) << std::endl;
        // 根据输入调用对应函数（执行技能，查找信息，跳过回合）
        if (input.find("execute") == 0) {
            int skill_res = Execute(input, team, code, friend_positionArray, enemy_positionArray, waitingQueue, flag);
            if (skill_res == 1) {
                check_combatInfo(friend_positionArray, enemy_positionArray);
                // 检测游戏是否结束
                isGameOver = isGameFinish(friend_positionArray, enemy_positionArray) ? 1 : 0;
                if (isGameOver) isRoundOver = 1;
            } else continue;
        } else if (input.find("query") == 0) {
            Query(input, code, friend_positionArray, enemy_positionArray, waitingQueue, flag);
            continue;
        } else if (input == "skip") {
            skip_res = Skip(waitingQueue, *flag);
            // 如果skip成功执行则结束本回合，进入下一回合
            if (skip_res == true) isRoundOver = true;
        } else std::cout << "输入命令语句无效，请重新输入！ERROR:0x0c" << std::endl;
    }
    return isGameOver;
}
