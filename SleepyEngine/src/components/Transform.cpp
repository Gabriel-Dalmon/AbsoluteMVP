#include "pch.h"
#include "Transform.h"

Transform::Transform(){}

Transform::~Transform(){}

//this function set every members to their initial value
void Transform::Identity()
{
	XMStoreFloat4x4(&m_scaleMatrix, XMMatrixIdentity());

	m_right = { 1.0f, 0.0f, 0.0f };
	m_up    = { 0.0f, 1.0f, 0.0f };
	m_dir   = { 0.0f, 0.0f, 1.0f };

	m_currentRotateQuat = { 0.0f, 0.0f, 0.0f, 1.0f }; 
	m_scaleVect         = { 1.0f, 1.0f, 1.0f };

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
	rotationMatrix = XMMatrixRotationQuaternion(rotateQuat);

	//and we store our axis
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

void Transform::SetRotation(Transform* transform)
{
	m_right = transform->m_right;
	m_up = transform->m_up;
	m_dir = transform->m_dir;
	
	m_currentRotateMatrix = transform->m_currentRotateMatrix;
	m_currentRotateQuat = transform->m_currentRotateQuat;
}

void Transform::SetRotation(float x, float y, float z)
{
	m_right.x = x;
	m_up.y = y;
	m_dir.z = z;
}

void Transform::LookAt(float x, float y, float z)
{
	XMVECTOR up = XMVectorSet(0, 1, 0, 1);
	XMVECTOR trg = XMVectorSet(x, y, z, 1);

	XMMATRIX m = XMMatrixLookAtLH(XMLoadFloat3(&m_positionVect), trg, up);
	m = XMMatrixInverse(nullptr, m);
	//XMFLOAT4X4 mm;
	//XMStoreFloat4x4(&mm, m);
	//mm._41 = 0.0f;
	//mm._42 = 0.0f;
	//mm._43 = 0.0f;
	//m = XMLoadFloat4x4(&mm);
	XMVECTOR q = XMQuaternionRotationMatrix(m);

	XMMATRIX rotationMatrix;
	rotationMatrix = XMMatrixRotationQuaternion(q);

	XMStoreFloat3(&m_right, rotationMatrix.r[0]);
	XMStoreFloat3(&m_up, rotationMatrix.r[1]);
	XMStoreFloat3(&m_dir, rotationMatrix.r[2]);

	XMStoreFloat4(&m_currentRotateQuat, q); 
	XMStoreFloat4x4(&m_currentRotateMatrix, rotationMatrix); 
}

void Transform::LookAt(Transform* transform)
{
	XMVECTOR up = XMVectorSet(0, 1, 0, 1);
	XMVECTOR trg = XMLoadFloat3(&transform->m_positionVect);

	XMMATRIX m = XMMatrixLookAtLH(XMLoadFloat3(&m_positionVect), trg, up); 

	// Si c'est une caméra qu'on doit regarder :
	m = XMMatrixInverse(nullptr, m); 
	//
	// 
	//XMFLOAT4X4 mm;
	//XMStoreFloat4x4(&mm, m);
	//mm._41 = 0.0f;
	//mm._42 = 0.0f;
	//mm._43 = 0.0f;
	//m = XMLoadFloat4x4(&mm);
	XMVECTOR q = XMQuaternionRotationMatrix(m);

	XMMATRIX rotationMatrix;
	rotationMatrix = XMMatrixRotationQuaternion(q);

	XMStoreFloat3(&m_right, rotationMatrix.r[0]);
	XMStoreFloat3(&m_up, rotationMatrix.r[1]);
	XMStoreFloat3(&m_dir, rotationMatrix.r[2]);

	XMStoreFloat4(&m_currentRotateQuat, q);
	XMStoreFloat4x4(&m_currentRotateMatrix, rotationMatrix);
}

