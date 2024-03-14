#include "pch.h"


CameraScript::CameraScript()
{
	SetLens(0.25f * MathHelper::Pi, 1.0f, 1.0f, 1000.0f);
}

CameraScript::~CameraScript()
{
}

void CameraScript::Initialize()
{
	m_pCam = m_pEntity->GetComponent<Camera>();
}

void CameraScript::SetLens(float fovY, float aspect, float zn, float zf)
{
	// cache properties
	m_pCam->mFovY = fovY;
	m_pCam->mAspect = aspect;
	m_pCam->mNearZ = zn;
	m_pCam->mFarZ = zf;

	m_pCam->mNearWindowHeight = 2.0f * m_pCam->mNearZ * tanf(0.5f * m_pCam->mFovY);
	m_pCam->mFarWindowHeight = 2.0f * m_pCam->mFarZ * tanf(0.5f * m_pCam->mFovY);

	XMMATRIX P = XMMatrixPerspectiveFovLH(m_pCam->mFovY, m_pCam->mAspect, m_pCam->mNearZ, m_pCam->mFarZ);
	XMStoreFloat4x4(&m_pCam->mProj, P);
}

void CameraScript::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
{
	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, pos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);
	XMStoreFloat3(&m_pCam->mPosition, pos);
	XMStoreFloat3(&m_pCam->mLook, L);
	XMStoreFloat3(&m_pCam->mRight, R);
	XMStoreFloat3(&m_pCam->mUp, U);

	m_pCam->mViewDirty = true;
}

void CameraScript::LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up)
{
	XMVECTOR P = XMLoadFloat3(&pos);
	XMVECTOR T = XMLoadFloat3(&target);
	XMVECTOR U = XMLoadFloat3(&up);

	LookAt(P, T, U);

	m_pCam->mViewDirty = true;
}

void CameraScript::Strafe(float d)
{
	// mPosition += d*mRight
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&m_pCam->mRight);
	XMVECTOR p = XMLoadFloat3(&m_pCam->mPosition);
	XMStoreFloat3(&m_pCam->mPosition, XMVectorMultiplyAdd(s, r, p));

	m_pCam->mViewDirty = true;
}

void CameraScript::Walk(float d)
{
	// mPosition += d*mLook
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat3(&m_pCam->mLook);
	XMVECTOR p = XMLoadFloat3(&m_pCam->mPosition);
	XMStoreFloat3(&m_pCam->mPosition, XMVectorMultiplyAdd(s, l, p));

	m_pCam->mViewDirty = true;
}

void CameraScript::Pitch(float angle)
{
	// Rotate up and look vector about the right vector.

	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&m_pCam->mRight), angle);

	XMStoreFloat3(&m_pCam->mUp, XMVector3TransformNormal(XMLoadFloat3(&m_pCam->mUp), R));
	XMStoreFloat3(&m_pCam->mLook, XMVector3TransformNormal(XMLoadFloat3(&m_pCam->mLook), R));

	m_pCam->mViewDirty = true;
}

void CameraScript::RotateY(float angle)
{
	// Rotate the basis vectors about the world y-axis.

	XMMATRIX R = XMMatrixRotationY(angle);

	XMStoreFloat3(&m_pCam->mRight, XMVector3TransformNormal(XMLoadFloat3(&m_pCam->mRight), R));
	XMStoreFloat3(&m_pCam->mUp, XMVector3TransformNormal(XMLoadFloat3(&m_pCam->mUp), R));
	XMStoreFloat3(&m_pCam->mLook, XMVector3TransformNormal(XMLoadFloat3(&m_pCam->mLook), R));

	m_pCam->mViewDirty = true;
}

void CameraScript::UpdateViewMatrix()
{
	if (m_pCam->mViewDirty)
	{
		XMVECTOR R = XMLoadFloat3(&m_pCam->mRight);
		XMVECTOR U = XMLoadFloat3(&m_pCam->mUp);
		XMVECTOR L = XMLoadFloat3(&m_pCam->mLook);
		XMVECTOR P = XMLoadFloat3(&m_pCam->mPosition);

		// Keep CameraScript's axes orthogonal to each other and of unit length.
		L = XMVector3Normalize(L);
		U = XMVector3Normalize(XMVector3Cross(L, R));

		// U, L already ortho-normal, so no need to normalize cross product.
		R = XMVector3Cross(U, L);

		// Fill in the view matrix entries.
		float x = -XMVectorGetX(XMVector3Dot(P, R));
		float y = -XMVectorGetX(XMVector3Dot(P, U));
		float z = -XMVectorGetX(XMVector3Dot(P, L));

		XMStoreFloat3(&m_pCam->mRight, R);
		XMStoreFloat3(&m_pCam->mUp, U);
		XMStoreFloat3(&m_pCam->mLook, L);

		m_pCam->mView(0, 0) = m_pCam->mRight.x;
		m_pCam->mView(1, 0) = m_pCam->mRight.y;
		m_pCam->mView(2, 0) = m_pCam->mRight.z;
		m_pCam->mView(3, 0) = x;

		m_pCam->mView(0, 1) = m_pCam->mUp.x;
		m_pCam->mView(1, 1) = m_pCam->mUp.y;
		m_pCam->mView(2, 1) = m_pCam->mUp.z;
		m_pCam->mView(3, 1) = y;

		m_pCam->mView(0, 2) = m_pCam->mLook.x;
		m_pCam->mView(1, 2) = m_pCam->mLook.y;
		m_pCam->mView(2, 2) = m_pCam->mLook.z;
		m_pCam->mView(3, 2) = z;

		m_pCam->mView(0, 3) = 0.0f;
		m_pCam->mView(1, 3) = 0.0f;
		m_pCam->mView(2, 3) = 0.0f;
		m_pCam->mView(3, 3) = 1.0f;

		m_pCam->mViewDirty = false;
	}
}