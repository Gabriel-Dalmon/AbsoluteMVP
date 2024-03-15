#pragma once

class Camera : public Component
{
public:

	Camera() {};
	~Camera() {};

	// Get View/Proj matrices.
	XMMATRIX GetView()const { return XMLoadFloat4x4(&mView); }
	XMMATRIX GetProj()const { return XMLoadFloat4x4(&mProj); }

	XMFLOAT4X4 GetView4x4f()const { return mView; };
	XMFLOAT4X4 GetProj4x4f()const { return mProj; };

	// Get frustum properties.
	float GetNearZ()const;
	float GetFarZ()const;
	float GetAspect()const;
	float GetFovY()const;
	float GetFovX()const;

	// Get near and far plane dimensions in view space coordinates.
	float GetNearWindowWidth()const;
	float GetNearWindowHeight()const;
	float GetFarWindowWidth()const;
	float GetFarWindowHeight()const;


public:
	// Cache frustum properties.
	float mNearZ = 0.0f;
	float mFarZ = 0.0f;
	float mAspect = 0.0f;
	float mFovY = 0.0f;
	float mNearWindowHeight = 0.0f;
	float mFarWindowHeight = 0.0f;

	bool mViewDirty = true;

	// Cache View/Proj matrices.
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();
};