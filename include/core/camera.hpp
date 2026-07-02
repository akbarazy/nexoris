#pragma once
#include "raylib.h"
#include "raymath.h"

class GameCamera {
private:
    Camera2D camera;
    Vector2 targetPosition;
    float followSpeed;
    float targetZoom;
    float minZoom;
    float maxZoom;
    float zoomSpeed;
    float shakeIntensity;
    float shakeDuration;
    float shakeTimer;
    Vector2 shakeOffset;

public:
    GameCamera(float renderWidth, float renderHeight);
    void Update(float deltaTime);
    void SetTargetPosition(Vector2 position);
    void SnapToTarget(Vector2 position);
    void AddZoom(float amount);
    void SetZoom(float zoom);
    void TriggerShake(float intensity, float duration);
    Camera2D GetRaylibCamera() const;
};
