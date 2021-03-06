﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class CannonBall : MonoBehaviour {

    public float forceOnFire = 300f;

    bool fire = false;
    bool canFire = true;

    public bool isKinematic = true;

    Rigidbody _rigidbody = null;

	// Use this for initialization
	void Start () {
		
	}

    private void Awake()
    {
        _rigidbody = GetComponent<Rigidbody>();

        if (isKinematic)
        {
            _rigidbody.isKinematic = true;
        }
        else
        {
            _rigidbody.isKinematic = false;
        }
    }
	
	// Update is called once per frame
	void Update ()
    {
        if (Input.anyKeyDown && canFire)
        {
            _rigidbody.isKinematic = false;
            _rigidbody.AddForce(transform.forward * forceOnFire);
            canFire = false;
        }
	}
}
