#include "core/camera.hpp"
#include <cstdlib>

GameCamera::GameCamera(float renderWidth, float renderHeight)
{
    camera = { 0 };
    camera.offset = { renderWidth * 0.5f, renderHeight * 0.5f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    targetPosition = { 0.0f, 0.0f };
    followSpeed = 5.0f;
    
    targetZoom = 1.0f;
    minZoom = 1.0f;
    maxZoom = 2.5f;
    zoomSpeed = 8.0f;
    
    shakeIntensity = 0.0f;
    shakeDuration = 0.0f;
    shakeTimer = 0.0f;
    shakeOffset = { 0.0f, 0.0f };
}

void GameCamera::Update(float deltaTime)
{
    camera.target = Vector2Lerp(camera.target, targetPosition, followSpeed * deltaTime);
    camera.zoom = Lerp(camera.zoom, targetZoom, zoomSpeed * deltaTime);
    
    if (shakeTimer > 0.0f)
    {
        shakeTimer -= deltaTime;
        
        float decay = shakeTimer / shakeDuration;
        float currentIntensity = shakeIntensity * decay;
        
        float randomX = (std::rand() / (float)RAND_MAX) * 2.0f - 1.0f;
        float randomY = (std::rand() / (float)RAND_MAX) * 2.0f - 1.0f;
        
        float offsetX = randomX * currentIntensity;
        float offsetY = randomY * currentIntensity;
        
        shakeOffset = { offsetX, offsetY };
    }
    else
    {
        shakeOffset = { 0.0f, 0.0f };
    }
}

void GameCamera::SetTargetPosition(Vector2 position)
{
    targetPosition = position;
}

void GameCamera::SnapToTarget(Vector2 position)
{
    targetPosition = position;
    camera.target = position;
}

void GameCamera::AddZoom(float amount)
{
    targetZoom += amount;
    if (targetZoom < minZoom) targetZoom = minZoom;
    if (targetZoom > maxZoom) targetZoom = maxZoom;
}

void GameCamera::SetZoom(float zoom)
{
    targetZoom = zoom;
    if (targetZoom < minZoom) targetZoom = minZoom;
    if (targetZoom > maxZoom) targetZoom = maxZoom;
}

void GameCamera::TriggerShake(float intensity, float duration)
{
    shakeIntensity = intensity;
    shakeDuration = duration;
    shakeTimer = duration;
}

Camera2D GameCamera::GetRaylibCamera() const
{
    Camera2D viewCamera = camera;
    
    viewCamera.offset.x += shakeOffset.x;
    viewCamera.offset.y += shakeOffset.y;
    
    return viewCamera;
}
