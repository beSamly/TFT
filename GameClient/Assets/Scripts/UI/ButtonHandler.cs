using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Network;
using UnityEngine.UI;
using Assets;

public class ButtonHandler : MonoBehaviour
{
    private GameSystem gameSystem;

    [SerializeField]
    public Text inputField;

    private void Awake()
    {
        GameSystem[] gameSystemList = GameObject.FindObjectsOfType<GameSystem>();
        gameSystem = gameSystemList[0];
    }

    public void OnClickEnterButton()
    {
        gameSystem.networkController.SendLoginRequest(inputField.text);
    }

    public void OnClickAiMatch()
    {
        gameSystem.networkController.SendAiMatchRequest();

    }
}
