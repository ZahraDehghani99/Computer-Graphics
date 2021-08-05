using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Linq;

public class GameManager : MonoBehaviour
{
    // for reach to all other scripts
    public static GameManager Instance { get; set; }

    public int length;

    public Text length_text;

    public GameObject GameOverPanel;

 
    private void Awake()
    {
        Instance = this;
    }


    public void GameOver()
    {
        GameOverPanel.SetActive(true);

    }

    public void OnTryAgain()
    {
        SceneManager.LoadScene(0);
    }
}
