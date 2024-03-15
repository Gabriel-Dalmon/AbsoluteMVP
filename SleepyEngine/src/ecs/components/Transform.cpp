#include "pch.h"

Transform::Transform(){
	m_typeFlag = TRANSFORM;
}

Transform::~Transform(){}

//this function set every members to their initial value
void Transform::Initialize()
{
	XMStoreFloat4x4(&m_scaleMatrix, XMMatrixIdentity());
	(m_scaleVect.x, m_scaleVect.y, m_scaleVect.z) = (0.0f, 0.0f, 0.0f);
	(m_dir.x, m_dir.y, m_dir.z) = (1.0f, 0.0f, 0.0f);
	(m_right.x, m_right.y, m_right.z) = (0.0f, 1.0f, 0.0f);
	(m_up.x, m_up.y, m_up.z) = (0.0f, 0.0f, 1.0f);
	(m_currentRotateQuat.x, m_currentRotateQuat.y, m_currentRotateQuat.z, m_currentRotateQuat.w) = (0.0f, 0.0f, 0.0f, 1.0f);
	XMStoreFloat4x4(&m_currentRotateMatrix, XMMatrixIdentity());
	(m_positionVect.x, m_positionVect.y, m_positionVect.z) = (0.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&m_positionMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_transformMatrix, XMMatrixIdentity());
}


void Transform::Rotate(float yaw, float pitch, float roll)
{
	XMVECTOR quat;
	XMVECTOR rotateQuat = XMVectorZero();
	

	//roll calcul
	XMVECTOR up;
	up = XMLoadFloat3(&m_up);
	quat = XMQuaternionRotationAxis(up, roll);
	rotateQuat = XMQuaternionMultiply(rotateQuat, quat);

	//pitch calcul
	XMVECTOR right;
	right = XMLoadFloat3(&m_right);
	quat = XMQuaternionRotationAxis(right, pitch);
	rotateQuat = XMQuaternionMultiply(rotateQuat, quat);

	//yaw calcul
	XMVECTOR dir;
	dir = XMLoadFloat3(&m_dir);
	quat = XMQuaternionRotationAxis(dir,yaw);
	rotateQuat = quat;

	//we then use that to operate on matrices
	XMVECTOR currentRotateQuat;
	currentRotateQuat = XMLoadFloat4(&m_currentRotateQuat);

	rotateQuat = XMQuaternionMultiply(rotateQuat, currentRotateQuat);

	XMMATRIX rotationMatrix;
	rotationMatrix =  XMMatrixRotationQuaternion(rotateQuat);

	//and we store our axis
	XMVECTOR storageBuffer = XMVectorZero();

	XMVectorSetX(storageBuffer, XMVectorGetX(rotationMatrix.r[0]));
	XMVectorSetY(storageBuffer, XMVectorGetY(rotationMatrix.r[0]));
	XMVectorSetZ(storageBuffer, XMVectorGetZ(rotationMatrix.r[0]));
	XMStoreFloat3(&m_right, storageBuffer);

	XMVectorSetX(storageBuffer, XMVectorGetX(rotationMatrix.r[1]));
	XMVectorSetY(storageBuffer, XMVectorGetY(rotationMatrix.r[1]));
	XMVectorSetZ(storageBuffer, XMVectorGetZ(rotationMatrix.r[1]));
	XMStoreFloat3(&m_dir, storageBuffer);

	XMVectorSetX(storageBuffer, XMVectorGetX(rotationMatrix.r[2]));
	XMVectorSetY(storageBuffer, XMVectorGetY(rotationMatrix.r[2]));
	XMVectorSetZ(storageBuffer, XMVectorGetZ(rotationMatrix.r[2]));
	XMStoreFloat3(&m_up, storageBuffer);

	XMStoreFloat4x4(&m_currentRotateMatrix, rotationMatrix);
}

void Transform::SetPosition(float x, float y, float z)
{
	XMMATRIX position = XMMatrixTranslation(x, y, z);
	XMStoreFloat4x4(&m_positionMatrix, position);
	(m_positionVect.x, m_positionVect.y, m_positionVect.z) = (x, y, z);
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