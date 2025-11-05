use std::io::{self, BufRead};

pub fn read_matrix() -> Vec<Vec<i32>> {
    let stdin = io::stdin();

    let matrix: Vec<Vec<i32>> = stdin
        .lock()
        .lines()
        .map(|line|
            line.unwrap().chars().map(|c| c as i32).collect())
        .collect();

    return matrix;
}

pub fn part_1(){
    let mut matrix = read_matrix();

    let width = matrix[0].len() as i32; 
    let height = matrix.len() as i32;

    let neighbours = |pos: (i32, i32)| {
        return vec![(pos.0+1, pos.1),(pos.0-1, pos.1),(pos.0, pos.1+1),(pos.0, pos.1-1)];
    };

    let is_pos_valid = |pos: (i32, i32)|{
        return pos.0 >= 0 && pos.1 >= 0 && pos.0 < (width as i32) && pos.1 < (height as i32);
    };

    let mut pointer = 0 as i32;
    let mut total_cost = 0;

    while pointer < width*height {
        while pointer < width*height && matrix[(pointer / width) as usize][(pointer % width) as usize] < 0 {
            pointer += 1;
        }
        if pointer >= width*height {
            break;
        }

        let mut stack: Vec<(i32, i32)> = Vec::new();
        stack.push((pointer % width, pointer/width));
        let curr_plant = matrix[(pointer / width) as usize][(pointer % width) as usize];
        let mut area = 0;
        let mut perimeter = 0;

        while let Some(curr_pos) = stack.pop(){
            if matrix[curr_pos.1 as usize][curr_pos.0 as usize] < 0 {
                continue;
            }

            area += 1;
            matrix[curr_pos.1 as usize][curr_pos.0 as usize] = -curr_plant;

            for n in neighbours(curr_pos){
                if !is_pos_valid(n){
                    perimeter+=1;
                    continue;
                }
            
                if matrix[n.1 as usize][n.0 as usize] != curr_plant && matrix[n.1 as usize][n.0 as usize] != -curr_plant{
                    perimeter+=1;
                    continue;
                }

                stack.push(n);
            }
        }

        println!("plant: {:?} area: {:?} perimeter {:?}", curr_plant, area, perimeter);

        total_cost += area*perimeter;
    }

    println!("Total cost: {:?}", total_cost);
}