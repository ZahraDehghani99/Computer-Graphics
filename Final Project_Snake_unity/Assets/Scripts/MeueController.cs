using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MeueController : MonoBehaviour
{
    // load SnakeGame Scene(1) when click on Play button
    public void onPlay()
    {
        SceneManager.LoadScene(1);
    }

    public void onExit()
    {
        Application.Quit();
    }
}
