//EntityHeaders.cpp - built by compiler

#ifdef SAVEHEADERS

if (typeid(*&entity).hash_code() == typeid(Flower).hash_code())
{
    file << " datTestFlower ";
    file.write((char *)(&entity), sizeof(Flower));
}
else if (typeid(*&entity).hash_code() == typeid(Bunny).hash_code())
{
    file << " datTestBunny ";
    file.write((char *)(&entity), sizeof(Bunny));
}

#endif



#ifdef LOADHEADERS

//Read in identifier
string entityType = "";
while (file >> entityType)
{
    //cerr << '.';

    //read the space seperator
    file.read(&byte, 1);

    if (entityType == "datTestFlower")
    {
        cerr << "1\n";
        Flower* entityP = new Flower(0,0,this);
        cerr << "2\n";
        auto* stuff = &typeid(*entityP);
        std::cerr << stuff << std::endl;
        file.read((char *)entityP, sizeof(Flower));
        cerr << "3\n";
        // std::cerr << &typeid(*entityP) << std::endl;
        entityP->bin = this;
        cerr << "4\n";
        insert(entityP);
        cerr << "5\n";
    }
    else if (entityType == "datTestBunny")
    {
        Bunny* entityP = new Bunny(0,0,this);
        file.read((char *)entityP, sizeof(Bunny));
        entityP->bin = this;
        insert(entityP);
    }
    else
    {
        cerr << "Something went very wrong: " << entityType << ".\n";
    }
}


#endif
