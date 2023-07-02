#include "Player.h"
#include"Trunsform.h"
#include"MeshRenderer.h"
#include"JobScheguler.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_sModelName = "Player";
	AddComponent<Trunsform>();
	AddComponent<MeshRenderer>();
}
