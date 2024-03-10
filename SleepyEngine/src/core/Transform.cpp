#include "pch.h"

Transform::Transform(){}

Transform::~Transform(){}

//this function set every members to their initial value
void Transform::Identity()
{
	XMStoreFloat4x4(&m_scaleMatrix, XMMatrixIdentity());

	m_right = { 1.0f, 0.0f, 0.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_dir = { 0.0f, 0.0f, 1.0f };

	m_currentRotateQuat = { 0.0f, 0.0f, 0.0f, 1.0f }; 
	m_scaleVect = { 1.0f, 1.0f, 1.0f };

	XMStoreFloat4x4(&m_currentRotateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_positionMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_transformMatrix, XMMatrixIdentity());
}


void Transform::Rotate(float yaw, float pitch, float roll)
{
	XMVECTOR quat;
	XMVECTOR rotateQuat;
	
	//pitch calcul
	XMVECTOR right;
	right = XMLoadFloat3(&m_right);
	quat = XMQuaternionRotationAxis(right, yaw);
	rotateQuat = quat;

	//roll calcul
	XMVECTOR up;
	up = XMLoadFloat3(&m_up);
	quat = XMQuaternionRotationAxis(up, pitch);
	rotateQuat = XMQuaternionMultiply(rotateQuat, quat);

	//yaw calcul
	XMVECTOR dir;
	dir = XMLoadFloat3(&m_dir);
	quat = XMQuaternionRotationAxis(dir,roll);
	rotateQuat = XMQuaternionMultiply(rotateQuat, quat);  

	//we then use that to operate on matrices
	XMVECTOR currentRotateQuat;
	currentRotateQuat = XMLoadFloat4(&m_currentRotateQuat);

	rotateQuat = XMQuaternionMultiply(rotateQuat, currentRotateQuat);

	XMMATRIX rotationMatrix;
	rotationMatrix =  XMMatrixRotationQuaternion(rotateQuat);

	//and we store our axis
	XMVECTOR storageBuffer = XMVectorZero();

	XMStoreFloat3(&m_right, rotationMatrix.r[0]);
	XMStoreFloat3(&m_up, rotationMatrix.r[1]);
	XMStoreFloat3(&m_dir, rotationMatrix.r[2]);

	XMStoreFloat4(&m_currentRotateQuat, rotateQuat); 
	XMStoreFloat4x4(&m_currentRotateMatrix, rotationMatrix);  
}  

void Transform::Update()  
{
	XMMATRIX scale = XMLoadFloat4x4(&m_scaleMatrix);
	XMMATRIX rotate = XMLoadFloat4x4(&m_currentRotateMatrix);
	XMMATRIX position = XMLoadFloat4x4(&m_positionMatrix);
	XMMATRIX transform;
	transform = scale;
	transform *= rotate;
	transform *= position;
	XMStoreFloat4x4(&m_transformMatrix, transform);
}

void Transform::SetScale(float x, float y, float z)
{
	m_scaleVect.x = x;
	m_scaleVect.y = y;
	m_scaleVect.z = z;

	XMMATRIX mScaTemp = XMMatrixScaling(m_scaleVect.x, m_scaleVect.y, m_scaleVect.z);

	XMStoreFloat4x4(&m_scaleMatrix, mScaTemp);
}

void Transform::SetPosition(float x, float y, float z)
{
	m_positionVect.x = x; 
	m_positionVect.y = y;  
	m_positionVect.z = z; 

	XMMATRIX mPosTemp = XMMatrixTranslation(m_positionVect.x, m_positionVect.y, m_positionVect.z); 

	XMStoreFloat4x4(&m_positionMatrix, mPosTemp); 
}
