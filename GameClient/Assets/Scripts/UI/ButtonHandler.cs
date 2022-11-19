using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Network;
using UnityEngine.UI;

public class ButtonHandler : MonoBehaviour
{

    [SerializeField]
    public NetworkController networkController;

    [SerializeField]
    public Text inputField;

    public void OnClickEnterButton()
    {
        networkController.SendLoginRequest(inputField.text);
    }
}
