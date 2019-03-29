﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour {
    public Transform prefab;
    private float timer = 0f;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        if( Input.GetKey(KeyCode.Space) == true && timer >= 0.3f)
        {
            Instantiate(prefab, transform.position, Quaternion.identity);
            timer = 0;
        }
        timer += Time.deltaTime;
		
	}
}
