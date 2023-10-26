import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import XWingCommand 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("XWingCommand")

    property bool isServoConnected: false;
    property bool isServoToggled: false;

    SerialPort {
        id: _serialPort;
    }

    // TODO: List of available Ports

    Button {
        id: _portConnectButton
        text: "Connect"
        onClicked: {
            isServoConnected = _serialPort.connectPixhawk("COM13");
            _portConnectButton.text = isServoConnected ? "Disconnect" : "Connect";
        }
    }

    Button {
        id: _toggleServoButton
        text: "Turn on"
        anchors.top: _portConnectButton.bottom;
        enabled: isServoConnected;
        onClicked: {
            isServoToggled = _serialPort.toggleServo();
            _toggleServoButton.text = isServoToggled ? "Turn off" : "Turn on";
        }
    }
}
