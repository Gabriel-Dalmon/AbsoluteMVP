#pragma once

class Transform : public Component
{
public:
	Transform();
	~Transform();

	// MEMBER VARIABLES
public:
	//scale
	XMFLOAT3 m_scaleVect = { 0.f,0.f,0.f};
	XMFLOAT4X4 m_scaleMatrix;

	//orientation
	XMFLOAT3 m_dir = { 0.f,0.f,0.f };
	XMFLOAT3 m_right = { 0.f,0.f,0.f };
	XMFLOAT3 m_up = { 0.f,0.f,0.f };
	XMFLOAT4 m_currentRotateQuat = { 0.f,0.f,0.f,0.f };
	XMFLOAT4X4 m_currentRotateMatrix = {};

	//position
	XMFLOAT3 m_positionVect = { 0.f,0.f,0.f };
	XMFLOAT4X4 m_positionMatrix = {};

	//"merged" matrix
	XMFLOAT4X4 m_transformMatrix = {};

	// METHODES
public:
	// Init
	void Initialize();

	// Methods
	void Rotate(float yaw, float pitch, float roll);
	void SetScale(float x, float y, float z);
	void SetPosition(float x, float y, float z);

	XMFLOAT4X4 GetTransformMatrix() const { return m_transformMatrix; };

	void LookAt(float x, float y, float z);

	void Update();
};
