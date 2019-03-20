using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class Raycasting : MonoBehaviour {

    public Material awakeMaterial = null;
    public Material sleepingMaterial = null;

    private Rigidbody _rigidbody = null;

    public bool inRange = false;

    public float xDir = 1;
    public float yDir = 0;
    public float zDir = 0;

    // Use this for initialization
    void Start () {
        _rigidbody = GetComponent<Rigidbody>();
	}
	
	// Update is called once per frame
	void Update () {
		
        if(Input.GetKey(KeyCode.W))
        {
            transform.position += transform.forward * 0.05f;
        }

        if (Input.GetKey(KeyCode.S))
        {
            transform.position += -transform.forward * 0.05f;
        }

    }

    private void FixedUpdate()
    {
        inRange = Physics.Raycast(transform.position, new Vector3(xDir, yDir, zDir), 1.0f);

        if (!inRange && sleepingMaterial != null)
        {
            GetComponent<MeshRenderer>().material = sleepingMaterial;
        }

        if(inRange && awakeMaterial != null)
        {
            GetComponent<MeshRenderer>().material = awakeMaterial;
        }

        Debug.DrawRay(transform.position, new Vector3(xDir, yDir, zDir), Color.red);
    }
}
