#include "communication_with_esp.h"
#include <Arduino.h>

void handleModeSwitch()
{
    if (previousMode != currentMode)
    {
        switch (currentMode)
        {
        case 0:
            MoveToStartPosition();
            footTargets[0] = {-80, 125, stdLegzHeight};
            footTargets[1] = {80, 125, stdLegzHeight};
            footTargets[2] = {-80, -125, stdLegzHeight};
            footTargets[3] = {80, -125, stdLegzHeight};
            break;
        case 1:
            MoveToStartPosition();
            footTargets[0] = {-60, 0, stdLegzHeight};
            footTargets[1] = {20, 0, stdLegzHeight};
            footTargets[2] = {-60, 0, stdLegzHeight};
            footTargets[3] = {20, 0, stdLegzHeight};
            STOP = true;

            break;
        }
        previousMode = currentMode;
    }
    else
    {
    }
}

void parseInput(String data)
{
    data.trim();

    if (data == "STOP")
    {
        STOP = true;
        return;
    }
    else
    {
        STOP = false;
    };

    if (data.startsWith("currentMode:"))
    {
        int modeIndex = data.indexOf(':') + 1;
        currentMode = data.substring(modeIndex, data.indexOf(',', modeIndex)).toInt();

        handleModeSwitch();

        switch (currentMode)
        {
        case 0:
            sscanf(data.c_str(),
                   "currentMode:%d,x:%d,y:%d,z:%d,pitch:%f,yaw:%f,roll:%f,MPU:%d\n",
                   &currentMode, &nextBodyx, &nextBodyy, &nextBodyz, &nextBodyPitch, &nextBodyYaw, &nextBodyRoll, &MPUint);
            MPU = (MPUint != 0);
            break;

        case 1:
            sscanf(data.c_str(),
                   "currentMode:%d,nextXSpeed:%f,nextYSpeed:%f,nextTurning:%f,MPU:%d\n",
                   &currentMode, &nextXSpeed, &nextYSpeed, &nextTurning, &MPUint);
            MPU = (MPUint != 0);
            break;

        case 2:
        case 3:
        case 4:
        case 5:
            Serial.println("Eror : Mode not set up");
            break;

        default:
            Serial.println("Error : No matching mode");
        }
    }
    else
    {
        Serial.println("Error : received unexpected data from the esp32");
    };
}

void printState()
{
    // USB Seriall print
    Serial.println("=== Controller ===");
    Serial.print("Mode: ");
    Serial.println(currentMode);
    Serial.print("STOP: ");
    Serial.println(STOP ? "YES" : "NO");

    if (STOP)
        return;

    switch (currentMode)
    {
    case 0:
        Serial.printf("X: %d, Y: %d, Z: %d\n", nextBodyx, nextBodyy, nextBodyz);
        Serial.printf("Pitch: %.2f, Yaw: %.2f, Roll: %.2f\n", nextBodyPitch, nextBodyYaw, nextBodyRoll);
        Serial.printf("Leg: 0, Roll: %.2f, Pitch: %.2f, Knee: %.2f\nLeg: 1, Roll: %.2f, Pitch: %.2f, Knee: %.2f\nLeg: 2, Roll: %.2f, Pitch: %.2f, Knee: %.2f\nLeg: 3, Roll: %.2f, Pitch: %.2f, Knee: %.2f\n",
                      nextRoll[0], nextPitch[0], nextKnee[0],
                      nextRoll[1], nextPitch[1], nextKnee[1],
                      nextRoll[2], nextPitch[2], nextKnee[2],
                      nextRoll[3], nextPitch[3], nextKnee[3]);

        break;

    case 1:
        Serial.printf("X Speed: %.2f, Y Speed: %.2f, Turning: %.2f\n", nextXSpeed, nextYSpeed, nextTurning);

        break;

    case 2:
    case 3:
    case 4:
    case 5:
        Serial.printf("Nothing");

        break;

    default:
        Serial.println("No controller data");
    }
}
