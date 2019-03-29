using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneController : MonoBehaviour {

	// Use this for initialization
	void Start ()
    {
		
	}
	
	// Update is called once per frame
	void Update ()
    {
		if (Input.GetKeyDown(KeyCode.RightArrow) && SceneManager.GetActiveScene().buildIndex < 8)
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
        else if(Input.GetKeyDown(KeyCode.RightArrow) && SceneManager.GetActiveScene().buildIndex > 7)
            SceneManager.LoadScene(0);

        if (Input.GetKeyDown(KeyCode.LeftArrow) && SceneManager.GetActiveScene().buildIndex > 0)
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex - 1);
        else if (Input.GetKeyDown(KeyCode.LeftArrow) && SceneManager.GetActiveScene().buildIndex < 1)
            SceneManager.LoadScene(8);

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            #if UNITY_STANDALONE
                        Application.Quit();
            #endif
            
            #if UNITY_EDITOR
                        UnityEditor.EditorApplication.isPlaying = false;
            #endif
        }
    }
}
