//Enticap
Bin::Enticap::Enticap(Entity* const newEntity, Hex* hexP)
            : entityP(newEntity), hexP(hexP) {}

Bin::Hex* Bin::Enticap::getHexP() const
{
    return hexP;
}

Bin::Enticap::~Enticap()
{
    delete entityP;
}

/*
Entity* Bin::Enticap::UID() const //UDI for entity = mem addr on heap
{
    return entityP;
}

size_t Bin::Enticap::TUID() const //Type Identifier
{
    return typeid(*entityP).hash_code();
}*/
