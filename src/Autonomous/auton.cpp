#include "Autonomous/auton.h"
#include "Autonomous/autonFunctions.h"
#include "Mechanics/botIntake.h"
#include "Utilities/robotInfo.h"
#include "Utilities/debugFunctions.h"
#include "preauton.h"
#include "main.h"


namespace {
    using namespace auton;
    using namespace botinfo;
    using debug::printOnController;


    void autonTest();

    void runAutonRedDown();
    void runAutonRedUp();
    void runAutonBlueDown();
    void runAutonBlueUp();
    void runAutonSkills();
    void runAutonSkillsCrossBarrier();
    void runAutonSkillsStrategicPush();
    void runAllianceWallStake();


    bool userRunningAutonomous = false;
    autonomousType auton_runType = autonomousType::BlueDown;
    int auton_allianceId;
}


void setAutonRunType(int allianceId, autonomousType autonType) {
    switch (autonType) {
        case autonomousType::RedDown:
            printOnController("Auton: RedDown");
            printf("Nearaw\n");
            botintake::setFilterColor("blue");
            break;
        case autonomousType::RedUp:
            printOnController("Auton: RedUp");
            printf("Nearaw Safe\n");
            botintake::setFilterColor("blue");
            break;
        case autonomousType::BlueDown:
            printOnController("Auton: BlueDown");
            printf("Nearel\n");
            botintake::setFilterColor("red");
            break;
        case autonomousType::BlueUp:
            printOnController("Auton: BlueUp");
            printf("Faraw\n");
            botintake::setFilterColor("red");
            break;
        case autonomousType::AutonSkills:
            printOnController("Auton: Skills");
            printf("AuSk\n");
            botintake::setFilterColor("none");
            break;
        case autonomousType::DrivingSkills:
            printOnController("Driving Skills");
            printf("DrSk\n");
            botintake::setFilterColor("none");
            break;
        default:
            printOnController("Auton: None");
            printf("None\n");
            botintake::setFilterColor("none");
            break;
    }
    auton_runType = autonType;
    auton_allianceId = allianceId;
}


void showAutonRunType() {
    setAutonRunType(auton_allianceId, auton_runType);
}


autonomousType getAutonRunType() {
    return auton_runType;
}


bool isUserRunningAuton() {
    return userRunningAutonomous;
}


void runAutonomous() {
    printf("Auton time!\n");
    userRunningAutonomous = false;
    switch (auton_runType) {
        case autonomousType::RedUp:
            runAutonRedUp();
            break;
        case autonomousType::RedDown:
            runAutonRedDown();
            break;
        case autonomousType::BlueUp:
            runAutonBlueUp();
            break;
        case autonomousType::BlueDown:
            runAutonBlueDown();
            break;
        case autonomousType::AutonSkills:
            // runAutonSkills();
            runAutonSkillsStrategicPush();
            break;
        case autonomousType::AllianceWallStake:
            runAllianceWallStake();
            break;
        case autonomousType::Test:
            autonTest();
        default:
            break;
    }
}


namespace {
    void autonTest() {
        setRotation(0.0);
        //driveAndTurnDistanceTiles(1.0, 0.0, 50.0, 100.0, defaultMoveTilesErrorRange, 6.0);
        //task::sleep(2000);
        // driveAndTurnDistanceTiles(1.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 3.0);
        // driveAndTurnDistanceTiles(-1.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 3.0);
        // driveAndTurnDistanceTiles(-1.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 3.0);
        // driveAndTurnDistanceTiles(2.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 3.0);
        // driveAndTurnDistanceTiles(-2.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 3.0);



        // driveAndTurnDistanceTilesMotionProfile(1.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 1.5);
        // driveAndTurnDistanceTilesMotionProfile(1.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 1.5);
        // driveAndTurnDistanceTilesMotionProfile(-1.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 1.5);
        // driveAndTurnDistanceTilesMotionProfile(-1.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 1.5);
        // driveAndTurnDistanceTilesMotionProfile(2.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 2.0);
        // driveAndTurnDistanceTilesMotionProfile(-2.0, 0.0, 100.0, 100.0, defaultMoveTilesErrorRange, 2.0);


        turnToAngle(90);
        // turnToAngle(-90);
        // turnToAngle(180);
        // turnToAngle(-180);
        // turnToAngle(0);
    }


    /// @brief Run the 15-seconds red-down autonomous.
    void runAutonRedDown() {
        timer autontimer;
        setRotation(-90.0);


        /* Start facing left */
        
        // Grab middle goal
        turnToAngle(-90.0);
        driveAndTurnDistanceTiles(-1.5, -90.0, 60);
        turnToAngle(-122.0);
        setGoalClampState(1, 0.8);
        driveAndTurnDistanceTiles(-0.67, -122.0, 30.0, 100.0, autonvals::defaultMoveTilesErrorRange, 3.0);
        turnToAngleVelocity(-107.0, 30.0, -halfRobotLengthIn * 0.75);
        
        task::sleep(300);
        setIntakeState(1);
        task::sleep(300);
        // Score 1 ring
        //turnToAngle(125.0);
        
        driveAndTurnDistanceTiles(0.3, -107.0, 40.0);
        
        task::sleep(750);


        // Drop goal
        //setIntakeState(0);
        turnToAngle(-64);
        setGoalClampState(0);

        // Intake bottom ring
        turnToAngle(-64);
        setIntakeTopState(0);
        setIntakeBottomState(1);
        driveAndTurnDistanceTiles(0.6, -64, 20.0, 100.0);


        // Grab bottom goal
        turnToAngle(-180.0);
        driveAndTurnDistanceTiles(-0.4, -180.0);
        driveAndTurnDistanceTiles(-0.37, -180.0, 20.0);
        setGoalClampState(1);


        // Score 1 ring
        setIntakeState(1);
        task::sleep(750);


        // Drop goal
        turnToAngle(-270.0);
        setIntakeState(0);
        setGoalClampState(0);


        // Touch the ladder
        driveAndTurnDistanceTiles(0.9, -270.0, 30.0, 100.0);
    }


    /// @brief Run the 15-seconds red-up autonomous.
    void runAutonRedUpNew() {
        
    }

    /// @brief Run the 15-seconds red-up autonomous.
    void runAutonRedUp() {
        timer autontimer;
        //setGoalClampState(1);
        setGoalClampState(0);
        setRotation(-90.0);

        // Grab goal
        driveAndTurnDistanceTiles(-1.2, -90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        setGoalClampState(1, 0.5);
        driveAndTurnDistanceTiles(-0.15, -90.0, 15.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        
        //driveAndTurnDistanceTiles(-0.3, 105.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        //driveAndTurnDistanceTiles(-0.4, 90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        // Intake middle up
        setIntakeState(1);
        task::sleep(1000);
        turnToAngle(55.0);
        driveAndTurnDistanceTiles(1.06, 55.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        task::sleep(500);
        driveAndTurnDistanceTiles(-0.16, 55.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        turnToAngle(0.0);
        task::sleep(500);
        driveAndTurnDistanceTiles(0.1, 0.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        turnToAngleVelocity(65.0, 70.0, -halfRobotLengthIn * 1.37);
        // driveAndTurnDistanceTiles(0.6, 0.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        task::sleep(750);
        //turnToAngle(-55.0, -halfRobotLengthIn * 0.75);
        //turnToAngle(0, halfRobotLengthIn * 0.75);
        // Intake up
        turnToAngleVelocity(0.0, 70.0, halfRobotLengthIn *0.7);
        driveAndTurnDistanceTiles(-0.3, 0.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);


        // Touch ladder
        while (autontimer.value() < 12.0) {
            task::sleep(20);
        }
        turnToAngle(-90.0);
        driveAndTurnDistanceTiles(0.6, -90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        setIntakeState(0, 1);
        driveAndTurnDistanceTiles(0.4, -90.0, 100.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        turnToAngle(-90);
        setGoalClampState(0, 0.5);
        task::sleep(2000);
        driveAndTurnDistanceTiles(2.0, 90.0, 30.0, 100.0, autonvals::defaultMoveTilesErrorRange, 2.0);
        //*/
    }


    /// @brief Run the 15-seconds blue-down autonomous.
    void runAutonBlueDown() {
        timer autontimer;
        setRotation(90.0);


        /* Start facing left */
        
        // Grab middle goal
        turnToAngle(90.0);
        driveAndTurnDistanceTiles(-1.5, 90.0, 60);
        turnToAngle(118.0, -halfRobotLengthIn * 0.5);
        setGoalClampState(1, 0.85);
        driveAndTurnDistanceTiles(-0.64, 118.0, 30.0, 100.0, autonvals::defaultMoveTilesErrorRange, 3.0);
        turnToAngleVelocity(110.0, 30.0, halfRobotLengthIn * 0.75);
        
        task::sleep(200);
        setIntakeState(1);

        // Score 1 ring
        //turnToAngle(125.0);
        
        turnToAngleVelocity(120.0, 30.0, halfRobotLengthIn * 0.75);
        driveAndTurnDistanceTiles(0.3, 120.0);
        
        task::sleep(750);


        // Drop goal
        //setIntakeState(0);
        turnToAngle(50.0);
        setGoalClampState(0);

        // Intake bottom ring
        // turnToAngle(48.5);
        setIntakeTopState(0);
        setIntakeBottomState(1);
        driveAndTurnDistanceTiles(0.6, 50.0, 20.0, 100.0);


        // Grab bottom goal
        turnToAngle(180.0);
        driveAndTurnDistanceTiles(-0.4, 180.0);
        driveAndTurnDistanceTiles(-0.4, 180.0, 20.0);
        setGoalClampState(1);


        // Score 1 ring
        setIntakeState(1);
        task::sleep(750);


        // Drop goal
        turnToAngle(270.0);
        setIntakeState(0);
        setGoalClampState(0);


        // Touch the ladder
        driveAndTurnDistanceTiles(0.9, 270.0, 30.0, 100.0);
    }


    /// @brief Run the 15-seconds blue-up autonomous.
    void runAutonBlueUpNew() {
        timer autontimer;
        //setGoalClampState(1);
        setGoalClampState(0);
        setRotation(90.0);

        // Grab goal
        driveAndTurnDistanceTiles(-1.1, 90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        setGoalClampState(1, 0.5);
        driveAndTurnDistanceTiles(-0.15, 90.0, 15.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        
        //driveAndTurnDistanceTiles(-0.3, 105.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        //driveAndTurnDistanceTiles(-0.4, 90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        // Intake middle up
        setIntakeState(1);
        task::sleep(500);
        turnToAngle(-32.0);
        driveAndTurnDistanceTiles(1.0, -32.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        task::sleep(700);
        turnToAngleVelocity(10, 50, halfRobotLengthIn * 0.7);
        driveAndTurnDistanceTiles(0.4, 10.0, 20.0, 100.0, autonvals::defaultMoveTilesErrorRange, 0.5);
        driveAndTurnDistanceTiles(-0.1, 10.0, 20.0, 100.0, autonvals::defaultMoveTilesErrorRange, 0.5);
        task::sleep(300);
        turnToAngleVelocity(94, 50);
        setIntakeState(0, 2);
        driveAndTurnDistanceTiles(1.2, 90.0, 50.0, 100.0, autonvals::defaultMoveWithInchesErrorRange);
        while (autontimer.value() < 12.0) {
            task::sleep(20);
        }
        turnToAngle(235);
        driveAndTurnDistanceTiles(2, 235, 100, 100, autonvals::defaultMoveTilesErrorRange, 1.0);
				
        // setIntakeState(-1,0.5);
        // setIntakeState(0,1);
				// driveAndTurnDistanceTiles
       /*
        driveAndTurnDistanceTiles(0.1, 0.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 0.5);
        turnToAngleVelocity(-65.0, 70.0, -halfRobotLengthIn * 1.37);
        // driveAndTurnDistanceTiles(0.6, 0.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        task::sleep(300);
        //turnToAngle(-55.0, -halfRobotLengthIn * 0.75);
        //turnToAngle(0, halfRobotLengthIn * 0.75);
        // Intake up
        turnToAngleVelocity(0.0, 70.0, halfRobotLengthIn * 0.7);
        driveAndTurnDistanceTiles(-0.3, 0.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);


        // Touch ladder
        turnToAngle(90.0);
        driveAndTurnDistanceTiles(0.6, 90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        driveAndTurnDistanceTiles(0.4, 90.0, 100.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        turnToAngle(-90);
        setGoalClampState(0, 0.5);
        task::sleep(2000);
        driveAndTurnDistanceTiles(2.0, -90.0, 30.0, 100.0, autonvals::defaultMoveTilesErrorRange, 2.0);
        //*/
    }

    /// @brief Run the 15-seconds blue-up autonomous.
    void runAutonBlueUp() {
        timer autontimer;
        //setGoalClampState(1);
        setGoalClampState(0);
        setRotation(90.0);

        // Grab goal
        driveAndTurnDistanceTiles(-1.2, 90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        setGoalClampState(1, 0.5);
        driveAndTurnDistanceTiles(-0.15, 90.0, 15.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        
        //driveAndTurnDistanceTiles(-0.3, 105.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        //driveAndTurnDistanceTiles(-0.4, 90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        // Intake middle up
        setIntakeState(1);
        task::sleep(1000);
        turnToAngle(-55.0);
        driveAndTurnDistanceTiles(1.06, -55.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        task::sleep(500);
        driveAndTurnDistanceTiles(-0.16, -55.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        turnToAngle(0.0);
        task::sleep(500);
        driveAndTurnDistanceTiles(0.1, 0.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        turnToAngleVelocity(-65.0, 70.0, -halfRobotLengthIn * 1.37);
        // driveAndTurnDistanceTiles(0.6, 0.0, 40.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        task::sleep(750);
        //turnToAngle(-55.0, -halfRobotLengthIn * 0.75);
        //turnToAngle(0, halfRobotLengthIn * 0.75);
        // Intake up
        turnToAngleVelocity(0.0, 70.0, halfRobotLengthIn *0.7);
        driveAndTurnDistanceTiles(-0.3, 0.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);


        // Touch ladder
        while (autontimer.value() < 12.0) {
            task::sleep(20);
        }
        turnToAngle(90.0);
        driveAndTurnDistanceTiles(0.6, 90.0, 60.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        setIntakeState(0, 1);
        driveAndTurnDistanceTiles(0.4, 90.0, 100.0, 100.0, autonvals::defaultMoveTilesErrorRange, 1.5);
        turnToAngle(-90);
        setGoalClampState(0, 0.5);
        task::sleep(2000);
        driveAndTurnDistanceTiles(2.0, -90.0, 30.0, 100.0, autonvals::defaultMoveTilesErrorRange, 2.0);
        //*/
    }


    /// @brief Run the skills autonomous.
    void runAutonSkills() {
    }


    void runAutonSkillsCrossBarrier() {
    }


    void runAutonSkillsStrategicPush() {
    }


    void runAllianceWallStake() {
        timer autontimer;
        setRotation(-180.0);


        // Go back 1 tile
        driveAndTurnDistanceTiles(-1.0, -180.0);


        // Score
        turnToAngle(-90.0);
        setIntakeState(1);
        
        while (autontimer.value() < 12.0) {
            task::sleep(20);
        }


        setIntakeState(0);


        driveAndTurnDistanceTiles(2.0, -90.0, 30.0, 100.0);
    }
}
